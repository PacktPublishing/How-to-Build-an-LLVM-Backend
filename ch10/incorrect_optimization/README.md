# Use LLVM tools to reduce isses #

In this exercise you need to leverage `llvm-reduce` or `bugpoint` to produce the smallest possible test case for the broken constant propagation implemented in `populate_function.cpp`.

Build the code using the steps below.

Then use `llvm-reduce` or `bugpoint` on `bugged_input.ll` to try to reduce the input IR.

When you have the reduced IR, try to fix the issue.

Hint, another similar instruction does the right thing in this implementation.

Hint 2, the correct implementation is available in the ch4 directory.

## Configure your build directory ##

```bash
cmake -GNinja -DCMAKE_BUILD_TYPE=Debug -DLLVM_DIR=<path/to/llvm/install>/lib/cmake/llvm -Bbuild .
```

This will initialize your build directory in `build` (the `-B` option) with Ninja (`-G` option).

You must have a version of LLVM installed at `<path/to/llvm/install>` for this to succeed.
Either build and install your own llvm (with the `install` target from your LLVM build) or install an [official LLVM release](https://releases.llvm.org/) package.

## Build ##

```bash
ninja -C build
```

This builds the default target in the build directory.

This should produce in the `build` directory a binary named `buggy_cst_propagation`.

## Run ##

```bash
./build/buggy_cst_propagation [input.ll|.bc]
```

This will run buggy implementation on `input.ll`.
Without any input, it runs on a pre-defined IR hardcoded in the main function.
The code should work on the pre-defined IR.

Next, running the following command should crash the program:
```bash
./build/buggy_cst_propagation bugged_input.ll
```

Now, your job is to reduce the IR in `bugged_input.ll` to find the minimal set of instructions that exposes the issue.
The goal of this exercise is to have you play with `llvm-reduce` or `bugpoint`, which are utilities provided by the LLVM infrastructure.
