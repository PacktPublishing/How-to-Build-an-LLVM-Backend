#ifndef LLVM_LIB_TARGET_MYTARGET_MYTARGETINSTRINFO_H
#define LLVM_LIB_TARGET_MYTARGET_MYTARGETINSTRINFO_H

#include "MyTargetRegisterInfo.h" // For the definition of the register class.
#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#define GET_INSTRINFO_ENUM            // This should be in MC
#define GET_INSTRINFO_MC_HELPER_DECLS // This should be in MC
#include "MyTargetGenInstrInfo.inc"

namespace llvm {

class MyTargetInstrInfo : public MyTargetGenInstrInfo {
public:
  MyTargetInstrInfo();
};
} // namespace llvm

#endif
