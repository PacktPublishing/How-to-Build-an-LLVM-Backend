#!/bin/bash
./build/buggy_cst_propagation $@

status=$?
# We filter out $status == 1 because this is our error code
# when the input file is empty, which is not what we are trying
# bugpoint to converge to.
if [ $status -ne 0 ] && [ $status -ne 1 ]; then
  # bugpoint expects an error code when something interesting happened.
  exit -1
fi

exit 0
