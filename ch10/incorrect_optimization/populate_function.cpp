#include "llvm/ADT/APInt.h"
#include "llvm/ADT/PostOrderIterator.h" // For ReversePostOrderTraversal.
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/CFG.h"       // To instantiate RPOTraversal.
#include "llvm/IR/Constants.h" // For ConstantInt.
#include "llvm/IR/Function.h"
#include "llvm/IR/InstrTypes.h" // For BinaryOperator, etc.
#include "llvm/IR/Instruction.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/Debug.h" // For errs().

#include <optional>

using namespace llvm;

// Helper function to deal with binary instructions.
static Value *visitBinary(Instruction &Instr, LLVMContext &Ctxt,
                          std::optional<APInt> (*Computation)(const APInt &,
                                                              const APInt &)) {
  assert(isa<BinaryOperator>(Instr) && "This is meant for binary instruction");

  auto *LHS = dyn_cast<ConstantInt>(Instr.getOperand(0));
  auto *RHS = dyn_cast<ConstantInt>(Instr.getOperand(1));
  if (!LHS || !RHS)
    return nullptr;

  // FIXME: Technically this API is not precise enough because we may want to
  // produce poison value for e.g., a division by zero.
  std::optional<APInt> Res = Computation(LHS->getValue(), RHS->getValue());
  if (!Res.has_value())
    return nullptr;
  auto NewConstant = ConstantInt::get(Ctxt, *Res);
  return NewConstant;
}

// Takes \p Foo and apply a simple constant propagation optimization.
// \returns true if \p Foo was modified (i.e., something had been constant
// propagated), false otherwise.
bool buggyConstantPropagation(Function &Foo) {

  if (Foo.empty())
    return false;

  LLVMContext &Ctxt = Foo.getParent()->getContext();
  bool MadeChanges = false;

  ReversePostOrderTraversal<Function *> RPOT(&Foo);
  for (BasicBlock *BB : RPOT) {
    // Early increment to be able to remove the instruction that we replaced
    // on-the-fly. The alternative is to accumulate the instructions to remove
    // in a worklist and delete them afterwards.
    for (Instruction &Instr : make_early_inc_range(*BB)) {
      Value *NewConstant = nullptr;
      switch (Instr.getOpcode()) {
      case Instruction::Add:
        NewConstant = visitBinary(
            Instr, Ctxt,
            [](const APInt &A, const APInt &B) -> std::optional<APInt> {
              return A + B;
            });
        break;
      case Instruction::Sub:
        NewConstant = visitBinary(
            Instr, Ctxt,
            [](const APInt &A, const APInt &B) -> std::optional<APInt> {
              return A - B;
            });
        break;
      case Instruction::Mul:
        NewConstant = visitBinary(
            Instr, Ctxt,
            [](const APInt &A, const APInt &B) -> std::optional<APInt> {
              return A * B;
            });
        break;
      case Instruction::SDiv:
        NewConstant = visitBinary(
            Instr, Ctxt,
            [](const APInt &A, const APInt &B) -> std::optional<APInt> {
              return A.sdiv(B);
            });
        break;
      case Instruction::UDiv:
        NewConstant = visitBinary(
            Instr, Ctxt,
            [](const APInt &A, const APInt &B) -> std::optional<APInt> {
              if (B.isZero())
                return std::nullopt;
              return A.udiv(B);
            });
        break;
      case Instruction::Shl:
        NewConstant = visitBinary(
            Instr, Ctxt,
            [](const APInt &A, const APInt &B) -> std::optional<APInt> {
              return A.shl(B);
            });
        break;
      case Instruction::LShr:
        NewConstant = visitBinary(
            Instr, Ctxt,
            [](const APInt &A, const APInt &B) -> std::optional<APInt> {
              return A.lshr(B);
            });
        break;
      case Instruction::AShr:
        NewConstant = visitBinary(
            Instr, Ctxt,
            [](const APInt &A, const APInt &B) -> std::optional<APInt> {
              return A.ashr(B);
            });
        break;
      case Instruction::And:
        NewConstant = visitBinary(
            Instr, Ctxt,
            [](const APInt &A, const APInt &B) -> std::optional<APInt> {
              return A & B;
            });
        break;
      case Instruction::Or:
        NewConstant = visitBinary(
            Instr, Ctxt,
            [](const APInt &A, const APInt &B) -> std::optional<APInt> {
              return A | B;
            });
        break;
      case Instruction::Xor:
        NewConstant = visitBinary(
            Instr, Ctxt,
            [](const APInt &A, const APInt &B) -> std::optional<APInt> {
              return A ^ B;
            });
        break;

      default:
        break;
      }
      if (NewConstant) {
        Instr.replaceAllUsesWith(NewConstant);
        Instr.eraseFromParent();
        MadeChanges = true;
      }
    }
  }
  return MadeChanges;
}
