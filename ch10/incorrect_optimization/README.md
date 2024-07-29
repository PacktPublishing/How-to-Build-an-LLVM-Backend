# Use LLVM tools to reduce isses #

In this exercise you need to leverage `llvm-reduce` or `bugpoint` to produce the smallest possible test case for the broken constant propagation implemented in `populate_function.cpp`.

Build the code using the steps below.

Then use `llvm-reduce` or `bugpoint` on `bugged_input.ll` to try to reduce the input IR.
The goal here is for you to figure out the `llvm-reduce` (or `bugpoint`) command line and supply the right script to drive the tool where you need.

When you have the reduced IR, try to fix the issue.

Hint, when reducing the issue, make sure to filter out the case where the input module is empty.
The generated executable will convert towards this otherwise.

Hint 2, another similar instruction does the right thing in this implementation.

Hint 3, the correct implementation is available in the ch4 directory.

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

## Solution ##

### With `llvm-reduce` ###

`llvm-reduce` assumes it found what you are looking for when the given test script returns success (status == 0)

We use that in `check.sh`.

To reproduce the problem with `llvm-reduce`, you should run the following command line:
```bash
llvm-reduce --test=check.sh bugged_input.ll
```

This command runs `llvm-reduce` while using `chech.sh` as the compilation and testing step.

Check the content of this file in this directory.

The resulting IR should resemble:
```
define i32 @bar() {
bb:
  %i3 = sdiv i32 0, 0
  ret i32 0
}
```

### With `bugpoint` ###

`bugpoint` is the opposite of `llvm-reduce` and assumes it found what you are looking for when the test script returns failure (status != 0).

We use that in `bugpoint-check.sh`.

To reproduce the problem with `bugpoint`, you should run the following command line:
```bash
bugpoint --compile-command=./bugpoint-check.sh --run-llc --compile-custom bugged_input.ll
```

This command tells `bugpoint` that the compile command and status is reported by `bugpoint-check.sh`.
More specifically the combination of `--compile-custom` and `--compile-command` says that we use a custom compile command and that command is given by the related option.

Then, we use `llc` (`--run-llc`) as the runner, meaning that `bugpoint` should not try to interpret or run the IR with the "safe" version.

The resulting IR should resemble:
```
define void @bar() {
bb:
  %i3 = sdiv i32 3, 0
  unreachable
}
```

Remember to use `opt -S` on the bitcode (`.bc`) to see the textual IR.
