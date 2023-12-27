#!/bin/bash

echo ex8
FileCheck --input-file input.txt check-file.txt

echo ex9
# Here we use two prefixes to enable the second set of check lines in check-file.txt.
# Alternatively, we could have written a new check-file.

# This will reject input.txt, since the faulty lines are here.
echo expected fail
FileCheck --input-file input.txt check-file.txt --check-prefixes='CHECK,SECOND-CHECK'

echo expected pass
grep -v '^#' input.txt | FileCheck check-file.txt --check-prefixes='CHECK,SECOND-CHECK'

