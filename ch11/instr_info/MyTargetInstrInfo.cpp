#include "MyTargetInstrInfo.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/CodeGen/MachineBasicBlock.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/IR/DebugLoc.h"
#include "llvm/Support/ErrorHandling.h"
#include <cassert>
#include <iterator>

#define GET_INSTRINFO_CTOR_DTOR
#define GET_INSTRINFO_MC_DESC    // This should be in MC
#define GET_INSTRINFO_MC_HELPERS // This should be in MC
#include "MyTargetGenInstrInfo.inc"

using namespace llvm;

MyTargetInstrInfo::MyTargetInstrInfo() : MyTargetGenInstrInfo() {}
