#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/Debug.h" // For errs().

using namespace llvm;

extern std::unique_ptr<Module> myBuildModule(LLVMContext &);
extern std::unique_ptr<Module> solutionBuildModule(LLVMContext &);

int main(int argc, char **argv) {
  LLVMContext Ctxt;
  bool hadError = false;
  for (int i = 0; i != 2; ++i) {
    bool isRefImpl = i == 0;
    std::unique_ptr<Module> CurModule =
        isRefImpl ? solutionBuildModule(Ctxt) : myBuildModule(Ctxt);
    const char *msg = isRefImpl ? "Reference" : "Your solution";

    outs() << "\n\n## Processing module from " << msg << " implementation\n";
    if (!CurModule) {
      outs() << "Nothing built\n";
      continue;
    }

    CurModule->print(errs(), /*AssemblyAnnotationWriter=*/nullptr);
    // verifyModule  returns true if it finds errors and
    // print them on the provided output stream (errs() here).
    if (verifyModule(*CurModule, &errs())) {
      errs() << msg << " does not verify\n";
      hadError |= true;
    }
  }

  return !hadError;
}
