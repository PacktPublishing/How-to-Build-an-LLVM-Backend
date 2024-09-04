#ifndef __SOLUTIONREGISTERINFO_H__
#define __SOLUTIONREGISTERINFO_H__

#include "llvm/ADT/BitVector.h"
#include "llvm/CodeGen/MachineBasicBlock.h"
#include <cstdint>

#define GET_REGINFO_HEADER
#define GET_REGINFO_ENUM // Technically this one belongs to MC.
#include "SolutionGenRegisterInfo.inc"

namespace llvm {
class MachineFunction;

class SolutionRegisterInfo : public SolutionGenRegisterInfo {
public:
  SolutionRegisterInfo() : SolutionGenRegisterInfo(Register()) {}

  BitVector getReservedRegs(const MachineFunction &MF) const override {
    return BitVector();
  }

  const MCPhysReg *
  getCalleeSavedRegs(const MachineFunction *MF) const override {
    return nullptr;
  }

  bool eliminateFrameIndex(MachineBasicBlock::iterator II, int SPAdj,
                           unsigned FIOperandNum,
                           RegScavenger *RS = nullptr) const override {
    return false;
  }

  Register getFrameRegister(const MachineFunction &MF) const override {
    return Register();
  }
};

} // end namespace llvm.

#endif
