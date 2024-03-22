#include "llvm/IR/Function.h"
#include "llvm/Pass.h"          // For FunctionPass & INITIALIZE_PASS.
#include "llvm/Support/Debug.h" // For errs().

using namespace llvm;

extern bool solutionConstantPropagation(llvm::Function &);

// The implementation of this function is generated at the end of this file. See
// INITIALIZE_PASS.
namespace llvm {
void initializeYourTurnConstantPropagationPass(PassRegistry &);
};

namespace {
class YourTurnConstantPropagation /* TODO: Fill in the blanks */ {
public:
  YourTurnConstantPropagation() /* TODO: Fill in the blanks */ {}

  // TODO: Fill in the blanks.
};
} // End anonymous namespace.

// TODO: Remove and add proper implementation
void llvm::initializeYourTurnConstantPropagationPass(PassRegistry &) {}

Pass *createYourTurnPassForLegacyPM() {
  return nullptr; // TODO: Fill in the blanks.
}
