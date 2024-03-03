#include "llvm/CodeGen/GlobalISel/MachineIRBuilder.h"
#include "llvm/CodeGen/MachineFrameInfo.h" // For CreateStackObject.
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineMemOperand.h" // For MachinePointerInfo.
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/Register.h"
#include "llvm/CodeGen/TargetOpcodes.h"     // For INLINEASM.
#include "llvm/CodeGenTypes/LowLevelType.h" // For LLT.
#include "llvm/IR/Function.h"
#include "llvm/IR/InstrTypes.h" // For ICMP_EQ.

using namespace llvm;

// The goal of this function is to build a MachineFunction that
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
// The proposed ABI is:
// - 32-bit arguments are passed through registers: w0, w1
// - 32-bit returned values are passed through registers: w0, w1
// w0 and w1 are given as argument of this Function.
//
// The local variable named var is expected to live on the stack.
MachineFunction *populateMachineIR(MachineModuleInfo &MMI, Function &Foo,
                                   Register W0, Register W1) {
  MachineFunction &MF = MMI.getOrCreateMachineFunction(Foo);

  // The type for bool.
  LLT I1 = LLT::scalar(1);
  // The type of var.
  LLT I32 = LLT::scalar(32);

  // To use to create load and store for var.
  MachinePointerInfo PtrInfo;
  Align VarStackAlign(4);

  // The type for the address of var.
  LLT VarAddrLLT = LLT::pointer(/*AddressSpace=*/0, /*SizeInBits=*/64);

  // The stack slot for var.
  int FrameIndex = MF.getFrameInfo().CreateStackObject(32, VarStackAlign,
                                                       /*IsSpillSlot=*/false);

  // TODO: Populate MF.
  return &MF;
}
