#ifndef SOLUTION_PASSWITHNEWPM_H
#define SOLUTION_PASSWITHNEWPM_H
#include "llvm/IR/PassManager.h" // For PassInfoMixin.

using namespace llvm;

namespace llvm {
class Function;
};

class SolutionConstantPropagationNewPass
    : public PassInfoMixin<SolutionConstantPropagationNewPass> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};
#endif
