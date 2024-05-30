#include "llvm/AsmParser/Parser.h" // For parseAssemblyString.
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Instructions.h" // For LoadInst.
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Use.h"
#include "llvm/IR/User.h"
#include "llvm/Support/Debug.h"     // For errs().
#include "llvm/Support/SourceMgr.h" // For SMDiagnostic.

using namespace llvm;

const char *InputIR =
    "@global = external global ptr, align 8\n"
    "@other_global = local_unnamed_addr global ptr @global, align 8\n"
    "\n"
    "define signext i8 @foo() {\n"
    "bb:\n"
    "  %i = load ptr, ptr @global, align 8\n"
    "  %i1 = load i8, ptr %i, align 1\n"
    "  ret i8 %i1\n"
    "}\n"
    "\n"
    "define signext i8 @bar() {\n"
    "bb:\n"
    "  %i = load ptr, ptr @global, align 8\n"
    "  %i1 = load i8, ptr %i, align 1\n"
    "  ret i8 %i1\n"
    "}\n";

int main() {
  LLVMContext Context;
  SMDiagnostic Err;
  std::unique_ptr<Module> MyModule = parseAssemblyString(InputIR, Err, Context);
  Function *BarFunc = MyModule->getFunction("bar");

  BasicBlock &Entry = *BarFunc->begin();

  auto &BarRes = *cast<LoadInst>(Entry.begin());

  Value *Global = BarRes.getOperand(0);
  for (User *UserOfGlobal : Global->users()) {
    auto *UserInstr = dyn_cast<Instruction>(UserOfGlobal);
    if (!UserInstr) {
      errs() << "Found a non-instruction use of global: " << *UserOfGlobal
             << '\n';
      continue;
    }
    Function *UserFunc = UserInstr->getParent()->getParent();
    if (UserFunc != BarFunc)
      errs() << "Went from bar to " << UserFunc->getName() << '\n';
  }
  return 0;
}
