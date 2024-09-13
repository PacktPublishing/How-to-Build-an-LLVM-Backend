def SOLUTION_BREAKVALUE : Instruction<> {
  let Namespace = "MyTarget";
  let OutOperandList = (outs GPR32:$dst0, GPR32:$dst1);
  let InOperandList = (ins GPR64:$src0);
}

def SOLUTION_LOADIMM32 : Instruction<> {
  let Namespace = "MyTarget";
  let isAsCheapAsAMove = true;
  let OutOperandList = (outs GPR32:$dst);
  let InOperandList = (ins i32imm:$imm);
}

