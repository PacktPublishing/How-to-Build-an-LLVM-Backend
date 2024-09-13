#include "MyTargetInstrInfo.h"
#include "MyTargetRegisterInfo.h"

#include "llvm/CodeGen/TargetRegisterInfo.h"
#include "llvm/Support/Debug.h" // For dbgs().

using namespace llvm;

int main() {
  MyTargetRegisterInfo MyTRI;
  MyTargetInstrInfo MyTII;
  TargetRegisterInfo *RegInfos[] = {&MyTRI};
  unsigned NbInstrs = MyTII.getNumOpcodes();
  dbgs() << "Found " << NbInstrs << " instructions for MyTarget.\n";
  dbgs() << "Print the non-generic ones:\n";
  for (unsigned i = 0; i != NbInstrs; ++i) {
    const MCInstrDesc &InstrDesc = MyTII.get(i);
    // Skip the generic opcode to focus on the target specific ones.
    if (InstrDesc.isPseudo())
      continue;

    dbgs() << MyTII.getName(i) << ":isAsCheapAsMove("
           << InstrDesc.isAsCheapAsAMove() << ")\t";
    for (auto [index, MCOI] : enumerate(InstrDesc.operands())) {
      if (MCOI.OperandType == MCOI::OperandType::OPERAND_REGISTER) {
        if (index < InstrDesc.getNumDefs())
          dbgs() << "(def)";
        dbgs() << MyTRI.getRegClassName(MyTRI.getRegClass(MCOI.RegClass));
      } else if (MCOI.OperandType == MCOI::OperandType::OPERAND_IMMEDIATE) {
        dbgs() << "imm";
      } else
        dbgs() << "other";
      dbgs() << ", ";
    }
    dbgs() << '\n';
  }
  return 0;
}
