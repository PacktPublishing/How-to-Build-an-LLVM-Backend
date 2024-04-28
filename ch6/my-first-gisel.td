include "llvm/Target/Target.td"

def : HwMode<"", []>;
def myii: InstrInfo;
def : Target {
  let InstructionSet = myii;
}
def x0 : Register<"x0"> ;
def GPR32 : RegisterClass<"myNamespace", [i32], 32, (add x0)>;
