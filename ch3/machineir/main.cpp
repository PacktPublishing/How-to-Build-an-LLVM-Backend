#include "llvm/CodeGen/MachineBasicBlock.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/Register.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h" // For InitializeAllTargets
#include "llvm/Target/TargetMachine.h"
#include "llvm/TargetParser/Triple.h"

using namespace llvm;

extern MachineFunction *solutionPopulateMachineIR(MachineModuleInfo &,
                                                  llvm::Function &, Register,
                                                  Register);
extern MachineFunction *populateMachineIR(MachineModuleInfo &,
                                                  llvm::Function &, Register,
                                                  Register);

bool checkFunctionCorrectness(MachineFunction *Res, Register W0, Register W1) {
  // Take care of the liveness since we did not explain how to do that.
  MachineBasicBlock *EntryBB = Res->empty() ? nullptr : &*Res->begin();
  if (EntryBB) {
    EntryBB->addLiveIn(W0);
    EntryBB->addLiveIn(W1);
  }
  Res->print(errs());
  if (!Res->verify()) {
    errs() << Res->getName() << " does not verify\n";
    return false;
  }
  return true;
}

int main() {
  // We have to initialize all the targets to get the registry initialized.
  InitializeAllTargets();
  // We need the MC layer as well to query the register information.
  InitializeAllTargetMCs();

  auto TT(Triple::normalize("aarch64--"));
  std::string Error;
  const Target *TheTarget = TargetRegistry::lookupTarget(TT, Error);
  if (!TheTarget) {
    errs() << TT << " is not available with this build of LLVM\n";
    return -1;
  }
  LLVMTargetMachine *LLVMTM = static_cast<LLVMTargetMachine *>(
      TheTarget->createTargetMachine(TT, "", "", TargetOptions(), std::nullopt,
                                     std::nullopt, CodeGenOptLevel::Default));
  MachineModuleInfoWrapperPass MMIWP(LLVMTM);
  LLVMContext Context;
  Module MyModule("MyModule", Context);
  MyModule.setDataLayout(LLVMTM->createDataLayout());

  Function *SolutionFoo = Function::Create(
      FunctionType::get(Type::getVoidTy(Context), /*IsVarArg=*/false),
      Function::ExternalLinkage, "solution_foo", MyModule);
  const TargetSubtargetInfo *STI = LLVMTM->getSubtargetImpl(*SolutionFoo);
  const TargetRegisterInfo *TRI = STI->getRegisterInfo();

  // Find the indices for W0 and W1.
  // Since we are not in AArch64 library we don't have access to the AArch64::W0
  // enums.
  StringRef W0Str = "W0";
  StringRef W1Str = "W1";
  Register W0 = 0;
  Register W1 = 0;
  for (unsigned i = 1, e = TRI->getNumRegs(); i != e && (!W0 || !W1); ++i) {
    if (!W0 && W0Str == TRI->getName(i)) {
      W0 = i;
      continue;
    }
    if (!W1 && W1Str == TRI->getName(i)) {
      W1 = i;
      continue;
    }
  }

  if (!W0 || !W1) {
    errs() << "Failed to found physical registers w0 and w1\n";
    return -1;
  }

  MachineFunction *Res =
      solutionPopulateMachineIR(MMIWP.getMMI(), *SolutionFoo, W0, W1);
  bool solutionIsCorrect = checkFunctionCorrectness(Res, W0, W1);

  Function *Foo = Function::Create(
      FunctionType::get(Type::getVoidTy(Context), /*IsVarArg=*/false),
      Function::ExternalLinkage, "foo", MyModule);

  MachineFunction *YourTurnRes =
      populateMachineIR(MMIWP.getMMI(), *Foo, W0, W1);
  bool yourTurnIsCorrect = checkFunctionCorrectness(YourTurnRes, W0, W1);


  return !(solutionIsCorrect && yourTurnIsCorrect);
}
