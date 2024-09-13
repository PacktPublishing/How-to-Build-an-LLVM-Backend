def ADDi32: Instruction<> {
  let Namespace = "MyTarget";
  let OutOperandList = (outs GPR32:$dst);
  let InOperandList = (ins GPR32:$src0, GPR32:$src1);
}

include "solution-instrinfo.td"
include "yourTurn-instrinfo.td"
