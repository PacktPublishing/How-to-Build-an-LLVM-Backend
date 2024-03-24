#ifndef SOLUTION_PASSWITHNEWPM_H
#define SOLUTION_PASSWITHNEWPM_H
#include "llvm/IR/PassManager.h" // For PassInfoMixin.

namespace llvm {
class Function;
};

class SolutionConstantPropagationNewPass
    : public llvm::PassInfoMixin<SolutionConstantPropagationNewPass> {
public:
  llvm::PreservedAnalyses run(llvm::Function &F,
                              llvm::FunctionAnalysisManager &AM);
};
#endif
