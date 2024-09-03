include "llvm/Target/Target.td"

def : HwMode<"", []>;
def myii: InstrInfo;
def YourTurn : Target {
  let InstructionSet = myii;
}

let Namespace = "yourTurn" in {
// Complete this description to describe a register hierarchy that looks like:
//               +-----------+-----------+-----------+
// 128-bit quad  |    q0     |    q1     |     q2    |
//               +-----+-----+-----+-----+-----------+
// 64-bit double |  d0 | d1  |  d2 |     |           |
//               +--+--+--+--+-----+-----+-----------+
// 32-bit single |s0|s1|s2|  |           |           |
//               +--+--+--+--+-----------+-----------+
//
// Empty cells mean that no architectural register exists for that cell (it
// is not addressable.)
def s0 : Register<"s0">;

} // end namespace yourTurn.

// Bonus point, create 1 register class per level.
// They would map respectively to f128, f64, and f32.
def SINGLES : RegisterClass<"yourTurn", [f32], 32, (add s0)>;

