# Enable LLVM debug capabilities #

In this exercise, we run an input module, `hadd_vector.ll` in the `O3` optimization pipeline (with `opt`).

The goal here is for you to find when the 4 adds in the input IR gets replaced in one horizontal add (llvm.vector.reduce.add.)

To find this, you need to use `-print-after-all` to find which pass does the transformation you are looking for.

Then use `-debug-only=found_pass` to see how it does the transformation.

Note: the `-debugxxx` options works only on builds of LLVM that enabled the assertions.

The steps below shows you how to produce the interesting command line invocations.

## Configure your build directory ##

```bash
cmake -GNinja -DCMAKE_BUILD_TYPE=Debug -DLLVM_DIR=<path/to/llvm/install>/lib/cmake/llvm -Bbuild .
```

This will initialize your build directory in `build` (the `-B` option) with Ninja (`-G` option).

You must have a version of LLVM installed at `<path/to/llvm/install>` for this to succeed.
Either build and install your own llvm (with the `install` target from your LLVM build) or install an [official LLVM release](https://releases.llvm.org/) package.

Note: Again if you use a plain release the steps that uses `-debugxxx` will fail.

## Build ##

```bash
ninja -C build
```

This builds the default target in the build directory.

This should produce in the `build` directory (showing only the relevant files):
* `hadd_vector.out.ll`: The output IR of the `opt -O3` pipeline
* `print_after_all_hadd_vector.out.ll.txt`: The command line output of `print-after-all` for `O3`.
* `print_before_slp_vectorizer_hadd_vector.out.ll`: The input IR before the SLP vectorizer (the full module not just the function.)
* `debug_slp_vectorizer_before_slp_vectorizer_hadd_vector.out.ll.txt`: The debug ouput of the SLP vectorizer.

## Solution ##

The optimization we want to identify here is the SLP vectorizer (as you may have guessed from the dump we saved :)).

