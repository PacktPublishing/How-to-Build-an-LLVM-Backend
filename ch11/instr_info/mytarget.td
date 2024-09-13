include "llvm/Target/Target.td"

include "reginfo.td"
include "instrinfo.td"

def MyTargetii: InstrInfo;
def MyTarget : Target {
  let InstructionSet = MyTargetii;
}

