#include "llvm/IR/Function.h"
#include "llvm/Support/Debug.h" // For errs().

#include "passWithNewPM.h"

using namespace llvm;

extern bool solutionConstantPropagation(llvm::Function &);

PreservedAnalyses
SolutionConstantPropagationNewPass::run(Function &F,
                                        FunctionAnalysisManager &AM) {
  errs() << "Solution New PM on " << F.getName() << "\n";
  bool MadeChanges = solutionConstantPropagation(F);
  if (!MadeChanges)
    return PreservedAnalyses::all();
  // Even if we made changes, we didn't touched the CFG.
  // So everything on that is still current.
  PreservedAnalyses PA;
  PA.preserveSet<CFGAnalyses>();
  return PA;
}
