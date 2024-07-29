#!/bin/bash
./build/buggy_cst_propagation $@

status=$?
# We filter out $status == 1 because this is our error code
# when the input file is empty, which is not what we are trying
# llvm-reduce to converge to.
if [ $status -ne 0 ] && [ $status -ne 1 ]; then
  # llvm-reduce expects 0 when something interesting happens.
  exit 0
fi

exit -1
