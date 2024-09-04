#include "SolutionRegisterInfo.h"
#include "YourTurnRegisterInfo.h"

#include "llvm/CodeGen/TargetRegisterInfo.h"
#include "llvm/MC/MCRegisterInfo.h" // For the RegUnit iterators.
#include "llvm/Support/Debug.h"     // For dbgs().

using namespace llvm;

int main() {
  SolutionRegisterInfo SolutionRI;
  YourTurnRegisterInfo YourTurnRI;
  TargetRegisterInfo *RegInfos[] = {&SolutionRI, &YourTurnRI};
  const char *RIName[] = {"Solution", "YourTurn"};
  // Go through the register units and print them
  for (unsigned i = 0; i < sizeof(RegInfos) / sizeof(RegInfos[0]); ++i) {
    dbgs() << "===== RegisterInfo for " << RIName[i] << "=====\n";
    TargetRegisterInfo *TRI = RegInfos[i];
    dbgs() << "== RegisterUnit ==\n";
    // Traverse all the units and print out which registers it touches.
    for (unsigned Unit = 0, E = TRI->getNumRegUnits(); Unit != E; ++Unit) {
      dbgs() << "RegUnit " << Unit << ":\t";
      for (MCRegUnitRootIterator RI(Unit, TRI); RI.isValid(); ++RI) {
        for (MCSuperRegIterator SI(*RI, TRI, true); SI.isValid(); ++SI) {
          dbgs() << TRI->getName(*SI) << ", ";
        }
        dbgs() << "\n";
      }
    }
    dbgs() << "== RegisterClass ==\n";
    for (const TargetRegisterClass *RegClass : TRI->regclasses()) {
      dbgs() << "RegClass " << TRI->getRegClassName(RegClass) << ":\t";
      for (Register Reg : *RegClass) {
        dbgs() << TRI->getName(Reg) << ", ";
      }
      dbgs() << "\n";
    }
    dbgs() << "======= End RegisterInfo ========\n\n\n";
  }
  return 0;
}
