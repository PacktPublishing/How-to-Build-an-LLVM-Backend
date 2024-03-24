#include "llvm/IR/Function.h"
#include "llvm/Pass.h"          // For FunctionPass & INITIALIZE_PASS.
#include "llvm/Support/Debug.h" // For errs().

using namespace llvm;

extern bool solutionConstantPropagation(llvm::Function &);

// The implementation of this function is generated at the end of this file. See
// INITIALIZE_PASS.
namespace llvm {
void initializeSolutionConstantPropagationPass(PassRegistry &);
};

namespace {
// The scope we want to modify is a Function.
class SolutionConstantPropagation : public FunctionPass {
public:
  // Used for the pass registry.
  static char ID;

  SolutionConstantPropagation() : FunctionPass(ID) {
    // Technically we do not need to put this in the constructor.
    // Usually this call lives in the uber InitializeAllXXX.
    initializeSolutionConstantPropagationPass(*PassRegistry::getPassRegistry());
  }

  // Main function of a FunctionPass.
  // Returns true if any change was made to F.
  bool runOnFunction(Function &F) override {
    errs() << "Solution Legacy called on " << F.getName() << '\n';
    return solutionConstantPropagation(F);
  }
};
} // End anonymous namespace.

// Anchor for this pass' ID.
char SolutionConstantPropagation::ID = 0;

// Initialize function used for the pass registration.
// This hooks up the command line option and gives general information
// about the pass' properties.
// This macro generates a llvm::initialize##passImplementationName##Pass
// function.
INITIALIZE_PASS(/*passImplementationName=*/SolutionConstantPropagation,
                /*commandLineArgName=*/"legacy-solution",
                /*name=*/"Legacy Solution", /*isCFGOnly=*/false,
                /*isAnalysis=*/false);

Pass *createSolutionPassForLegacyPM() {
  return new SolutionConstantPropagation();
}
