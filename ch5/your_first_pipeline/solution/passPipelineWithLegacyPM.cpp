#include "llvm/IR/LegacyPassManager.h"               // For legacy::PassManager.
#include "llvm/Transforms/IPO/AlwaysInliner.h"       // For inliner pass.
#include "llvm/Transforms/InstCombine/InstCombine.h" // For instcombine pass.
#include "llvm/Transforms/Utils.h"                   // For mem2reg pass.

using namespace llvm;

void runSolutionPassPipelineForLegacyPM(Module &MyModule) {
  legacy::PassManager LegacyPM;

  LegacyPM.add(createPromoteMemoryToRegisterPass());
  LegacyPM.add(createInstructionCombiningPass());
  LegacyPM.add(createAlwaysInlinerLegacyPass());

  LegacyPM.run(MyModule);
}