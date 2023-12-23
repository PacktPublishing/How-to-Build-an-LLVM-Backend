This directory contains example of how FileCheck can be used.

The examples are sorted in increasing order of complexity.
- ex1: Uses only the simplest form of directives
- ex2: Shows how to use more than one prefix
- ex3: Introduces keywords
- ex4: Shows how to add regex in the mix
- ex5: Introduces variables

Each example lives in its own directory.
Each directory follows the same structure:
- `README.md` describes what there is to see in this example
- `run.sh` contains the command to run to demonstrate the specific example
- `input.txt` contains the input of the example
- `check-file.txt` contains the patterns that FileCheck will match in `run.sh`

To run the example:
- Make sure that FileCheck is in your `PATH`
- Change directory to exN
- Open `run.sh` to see what is being tested
- Either:
  - run the commands manually by copy/pasting them, or
  - execute `bash run.sh`
