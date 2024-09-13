let Namespace = "MyTarget" in {
//        +-----+-----+
// 64-bit |  d0 | d1  |
//        +--+--+--+--+
// 32-bit |s0|s1|s2|s3|
//        +--+--+--+--+

// Declare the different subregister for our target.
// Parameters are size and offset.
// Indices for singles in double.
def sub32_low: SubRegIndex<32>;
def sub32_high: SubRegIndex<32, 32>;

// single registers.
def s0 : Register<"s0">;
def s1 : Register<"s1">;
def s2 : Register<"s2">;
def s3 : Register<"s3">;

// double registers are made of two single registers.
// The pattern is a bit irregular because we assume
// we have only 3 single registers.
def d0 : Register<"d0"> {
  let SubRegIndices = [sub32_low, sub32_high];
  let SubRegs = [s0, s1];
}
def d1 : Register<"d1"> {
  let SubRegIndices = [sub32_low, sub32_high];
  let SubRegs = [s2, s3];
}
} // end namespace MyTarget.

def GPR32 : RegisterClass<"MyTarget", [i32], 32, (sequence "s%u", 0, 3)>;
def GPR64 : RegisterClass<"MyTarget", [i64], 64, (add d0, d1)>;
