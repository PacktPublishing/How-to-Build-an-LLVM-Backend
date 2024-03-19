#include "llvm/AsmParser/Parser.h" // For parseAssemblyString.
#include "llvm/IR/Function.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/Debug.h"     // For errs().
#include "llvm/Support/SourceMgr.h" // For SMDiagnostic.

using namespace llvm;

extern bool myConstantPropagation(llvm::Function &);
extern bool solutionConstantPropagation(llvm::Function &);

bool checkFunctionCorrectness(llvm::Function &Res) {
  Res.print(errs());
  // verifyFunction returns true if it finds errors and
  // print them on the provided output stream (errs() here).
  if (verifyFunction(Res, &errs())) {
    errs() << Res.getName() << " does not verify\n";
    return false;
  }
  return true;
}

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

  bool solutionDidSomething =
      solutionConstantPropagation(*BarFunc);
  bool solutionIsCorrect = checkFunctionCorrectness(*BarFunc);

  bool yourTurnDidSomething =
      myConstantPropagation(*BarFunc);
  bool yourTurnIsCorrect = checkFunctionCorrectness(*BarFunc);

  if (!(solutionIsCorrect && yourTurnIsCorrect))
    return -1;

  if (solutionDidSomething) {
    if (!yourTurnDidSomething)
      outs() << "The solution managed to optimize something but you did not\n";
    else
      outs() << "Both your solution and the provided solution did something, which one is better?\n";
  } else if (yourTurnDidSomething) {
    outs() << "Nice! You managed to optimize something whereas the provided solution did not!";
  }

  return 0;
}
