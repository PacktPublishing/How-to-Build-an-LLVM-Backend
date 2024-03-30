#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h" // For the new PassManager.
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Passes/StandardInstrumentations.h"
#include "llvm/Transforms/IPO/AlwaysInliner.h"       // For inliner pass.
#include "llvm/Transforms/InstCombine/InstCombine.h" // For instcombine pass.
#include "llvm/Transforms/Utils/Mem2Reg.h"           // For mem2reg pass.

using namespace llvm;

void runSolutionPassPipelineForNewPM(Module &MyModule) {
  LLVMContext &Context = MyModule.getContext();
  // CAREFUL the order of the manager is important here since the destructor
  // needs to be called in the right order otherwise it will crash.
  FunctionAnalysisManager FAM;
  ModuleAnalysisManager MAM;

  PassInstrumentationCallbacks PIC;
  PrintPassOptions PrintPassOpts;
  PrintPassOpts.Verbose = true;
  PrintPassOpts.SkipAnalyses = false;
  PrintPassOpts.Indent = true;
  StandardInstrumentations SI(Context, /*DebugLogging=*/true,
                              /*VerifyEachPass=*/false, PrintPassOpts);
  SI.registerCallbacks(PIC, &MAM);

  // Register the passes used implicitly at the start of the pipeline.
  // And enable logging.
  MAM.registerPass([&] { return PassInstrumentationAnalysis(&PIC); });
  FAM.registerPass([&] { return PassInstrumentationAnalysis(&PIC); });
  // Well this one is not as implicit, we ask for it with the call to the
  // adaptor below.
  MAM.registerPass([&] { return FunctionAnalysisManagerModuleProxy(FAM); });
  FAM.registerPass([&] { return ModuleAnalysisManagerFunctionProxy(MAM); });
  ModulePassManager NewPM;
  FunctionPassManager FPMgr;

  // Populate the XXXAnalysisManager with the IDs for all the passes.
  PassBuilder PB;
  PB.registerFunctionAnalyses(FAM);
  PB.registerModuleAnalyses(MAM);

  // Wrap the function pass into a module pass.
#ifndef USE_MODULE_MGR
  FPMgr.addPass(PromotePass());
  FPMgr.addPass(InstCombinePass());
#else
  NewPM.addPass(createModuleToFunctionPassAdaptor(PromotePass()));
  NewPM.addPass(createModuleToFunctionPassAdaptor(InstCombinePass()));
#endif
  NewPM.addPass(createModuleToFunctionPassAdaptor(std::move(FPMgr)));
  NewPM.addPass(AlwaysInlinerPass());
  NewPM.run(MyModule, MAM);
}
