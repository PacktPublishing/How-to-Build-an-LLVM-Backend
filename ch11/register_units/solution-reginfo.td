include "llvm/Target/Target.td"

let Namespace = "Solution" in {
// Describe the following hiearchy.
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

// Declare the different subregister for our target.
// Parameters are size and offset.
// Indices for singles in double.
def sub32_low: SubRegIndex<32>;
def sub32_high: SubRegIndex<32, 32>;

// Indices for doubles in quad.
def sub64_low: SubRegIndex<64>;
def sub64_high: SubRegIndex<64, 64>;


// single registers.
def s0 : Register<"s0">;
def s1 : Register<"s1">;
def s2 : Register<"s2">;

// double registers are made of two single registers.
// The pattern is a bit irregular because we assume
// we have only 3 single registers.
def d0 : Register<"d0"> {
  let SubRegIndices = [sub32_low, sub32_high];
  let SubRegs = [s0, s1];
  let CoveredBySubRegs = true;
}
def d1 : Register<"d1"> {
  let SubRegIndices = [sub32_low];
  let SubRegs = [s2];
}
def d2 : Register<"d2">;

// quad registers are made of two double registers.
// Similar pattern as double registers.
def q0 : Register<"q0"> {
  let SubRegIndices = [sub64_low, sub64_high];
  let SubRegs = [d0, d1];
  let CoveredBySubRegs = true;
}
def q1 : Register<"q1"> {
  let SubRegIndices = [sub64_low];
  let SubRegs = [d2];
}
def q2 : Register<"q2">;
} // end namespace Solution.

// Bonus point: register classes.
def SINGLES : RegisterClass<"Solution", [f32], 32, (sequence "s%u", 0, 2)>;
def DOUBLES : RegisterClass<"Solution", [f64], 64, (sequence "d%u", 0, 2)>;
def QUADS : RegisterClass<"Solution", [f128], 128, (sequence "q%u", 0, 2)>;

// Boilerplate to get the TableGen backend happy.
def myii: InstrInfo;
def Solution : Target {
  let InstructionSet = myii;
}
