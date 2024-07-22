#include "llvm/ADT/ArrayRef.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"    // For ConstantInt.
#include "llvm/IR/DerivedTypes.h" // For PointerType, FunctionType.
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/Debug.h" // For errs().

#include <memory> // For unique_ptr

using namespace llvm;

// The goal of this function is to build a Module that
// represents the lowering of the following foo, a C function:
// extern int baz();
// extern void bar(int);
// void foo(int a, int b) {
//   int var = a + b;
//   if (var == 0xFF) {
//     bar(var);
//     var = baz();
//   }
//   bar(var);
// }
//
// The IR for this snippet (at O0) is:
// define void @foo(i32 %arg, i32 %arg1) {
// bb:
//   %i = alloca i32
//   %i2 = alloca i32
//   %i3 = alloca i32
//   store i32 %arg, ptr %i
//   store i32 %arg1, ptr %i2
//   %i4 = load i32, ptr %i
//   %i5 = load i32, ptr %i2
//   %i6 = add i32 %i4, %i5
//   store i32 %i6, ptr %i3
//   %i7 = load i32, ptr %i3
//   %i8 = icmp eq i32 %i7, 255
//   br i1 %i8, label %bb9, label %bb12
//
// bb9:
//   %i10 = load i32, ptr %i3
//   call void @bar(i32 %i10)
//   %i11 = call i32 @baz()
//   store i32 %i11, ptr %i3
//   br label %bb12
//
// bb12:
//   %i13 = load i32, ptr %i3
//   call void @bar(i32 %i13)
//   ret void
// }
//
// declare void @bar(i32)
// declare i32 @baz(...)
//
// This function contains a bug, can you spot it?
std::unique_ptr<Module> buggyBuildModule() {
  LLVMContext Ctxt;
  // Create the types that we will use over and over;
  Type *Int32Ty = Type::getInt32Ty(Ctxt);
  Type *VoidTy = Type::getVoidTy(Ctxt);
  Type *PtrTy = PointerType::get(Ctxt, /*AddrSpace=*/0);

  // Create the high level module.
  std::unique_ptr<Module> MyModule =
      std::make_unique<Module>("Solution Module", Ctxt);

  // Populate all the functions (just declaration for now.)
  // Starting with baz.
  FunctionType *BazTy =
      FunctionType::get(/*RetTy=*/Int32Ty, /*isVarArg=*/false);
  Function *BazFunc =
      cast<Function>(MyModule->getOrInsertFunction("baz", BazTy).getCallee());

  // bar.
  FunctionType *BarTy =
      FunctionType::get(VoidTy, /*ArgsTy=*/ArrayRef(Int32Ty), false);
  Function *BarFunc =
      cast<Function>(MyModule->getOrInsertFunction("bar", BarTy).getCallee());

  // foo.
  FunctionType *FooTy =
      FunctionType::get(VoidTy, /*ArgsTy*/ ArrayRef({Int32Ty, Int32Ty}), false);
  Function *FooFunc =
      cast<Function>(MyModule->getOrInsertFunction("foo", FooTy).getCallee());

  // Next, create the structure for foo.
  BasicBlock *BB = BasicBlock::Create(Ctxt, /*Name=*/"bb", /*Parent=*/FooFunc);
  BasicBlock *BB9 =
      BasicBlock::Create(Ctxt, /*Name=*/"bb9", /*Parent=*/FooFunc);
  BasicBlock *BB12 =
      BasicBlock::Create(Ctxt, /*Name=*/"bb12", /*Parent=*/FooFunc);

  // Populate bb.
  IRBuilder Builder(BB);
  // Allocate stack space for the local variables.
  Value *I = Builder.CreateAlloca(Int32Ty);
  Value *I2 = Builder.CreateAlloca(Int32Ty);
  Value *I3 = Builder.CreateAlloca(Int32Ty);
  // Get arg and arg1 from foo.
  Value *Arg = FooFunc->getArg(0);
  Value *Arg1 = FooFunc->getArg(1);
  // Store them in the "local" variables.
  Builder.CreateStore(Arg, I);
  Builder.CreateStore(Arg1, I2);
  // Reload from the local variables.
  Value *I4 = Builder.CreateLoad(Int32Ty, I);
  Value *I5 = Builder.CreateLoad(Int32Ty, I2);
  // Do the add.
  Value *I6 = Builder.CreateAdd(I4, I5);
  // Store to local variable i3.
  Builder.CreateStore(I6, I3);
  // Reload from i3 (now you understand why O0 is slow!!)
  Value *I7 = Builder.CreateLoad(Int32Ty, I3);
  // Compare.
  Value *Cst255 = ConstantInt::get(Int32Ty, 255);
  Value *I8 = Builder.CreateICmpEQ(I7, Cst255);
  // Then jump.
  Builder.CreateCondBr(I8, BB9, BB12);

  // Populate bb9.
  // Reset the builder on the next basic block.
  Builder.SetInsertPoint(BB9);
  // Reload the local variable i3.
  Value *I10 = Builder.CreateLoad(Int32Ty, I3);
  // Call bar with i10.
  Builder.CreateCall(BarFunc->getFunctionType(), BarFunc, ArrayRef(I10));
  // Call baz.
  Value *I11 = Builder.CreateCall(BazFunc->getFunctionType(), BazFunc);
  // Store the result in the local variable i3.
  Builder.CreateStore(I11, I3);
  // Jump to the next block.
  Builder.CreateBr(BB12);

  // Populate bb12.
  // Reset the builder on the next basic block.
  Builder.SetInsertPoint(BB12);
  // Reload the local variable I3.
  Value *I13 = Builder.CreateLoad(Int32Ty, I3);
  // Call bar on i13.
  Builder.CreateCall(BarFunc->getFunctionType(), BarFunc, ArrayRef(I13));
  // Create the final return.
  // Remember all basic block must end with a terminator.
  Builder.CreateRetVoid();

  return MyModule;
}
