#include "llvm/AsmParser/Parser.h" // For parseAssemblyString.
#include "llvm/IR/DerivedTypes.h"  // For VectorType and IntegerType.
#include "llvm/IR/Instruction.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IRReader/IRReader.h" // For parseIRFile.
#include "llvm/Support/Debug.h"     // For errs().
#include "llvm/Support/SourceMgr.h" // For SMDiagnostic.

using namespace llvm;

// Default input in case no file was provided.
const char *InputIR =
    "define <2 x i32> @foo(i32 %src) {\n"
    "bb:\n"
    "  %simd = insertelement <2 x i32> poison, i32 %src, i32 0\n"
    "  %input = insertelement <2 x i32> %simd, i32 %src, i32 1\n"
    "  %res = add <2 x i32> %input, %input\n"
    "  ret <2 x i32> %res\n"
    "}\n";

bool isVectorOfIntV1(Instruction &Add) {
  auto *VecTy = dyn_cast<VectorType>(Add.getType());
  return VecTy && isa<IntegerType>(VecTy->getElementType());
}

bool isVectorOfIntV2(Instruction &Add) {
  Type *Ty = Add.getType();
  return Ty->isVectorTy() && Ty->getScalarType()->isIntegerTy();
}

int main(int argc, char **argv) {
  LLVMContext Context;
  SMDiagnostic Err;
  std::unique_ptr<Module> MyModule;
  // To be able to play with the optimization a little bit,
  // support a mode where you can feed your own IR files.
  if (argc == 2) {
    outs() << "Reading module from '" << argv[1] << "'\n";
    MyModule = parseIRFile(argv[1], Err, Context);
  } else {
    MyModule = parseAssemblyString(InputIR, Err, Context);
  }
  if (!MyModule) {
    errs() << "Unable to build module\n";
    return -1;
  }

  for (Function &Func : *MyModule) {
    for (BasicBlock &BB : Func) {
      for (Instruction &Inst : BB) {
        if (Inst.getOpcode() != Instruction::Add)
          continue;
        bool IsVecIntTy1 = isVectorOfIntV1(Inst);
        bool IsVecIntTy2 = isVectorOfIntV2(Inst);
        if (IsVecIntTy1 != IsVecIntTy2)
          errs() << "Found a mismatch with v1 & v2 for " << Inst << '\n';
        if (IsVecIntTy1)
          outs() << "Found an add of vector int:\n" << Inst << '\n';
      }
    }
  }

  return 0;
}
