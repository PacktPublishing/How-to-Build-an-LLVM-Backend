# Easily find undefined behavior #

In this exercise you need to leverage the undefined sanitizer to find what is wrong with the `fctWithUB` function implemented in `populate_function.cpp`.

Build the code using the steps below.

Run it, play with different values.

Everything is fine, right?

No, this program relies on undefined behavior.

Rebuild with undefined sanitizer enable and find them.

To fix the UB, please implement the specifications put as comments before the implementation of `fctWithUB`.

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

This should produce in the `build` directory a binary named `use_after_free`.

## Run ##

```bash
./build/fct_w_ub -- someNumber
```

This will run the function that relies on UB on `someNumber`.

By default `someNumber == 12`.


## Solution ##

Configure your build with undefined sanitizer enabled and build:
```bash
cmake -GNinja -DCMAKE_BUILD_TYPE=Debug -DLLVM_DIR=<path/to/llvm/install>/lib/cmake/llvm -Bbuild_w_ubsan . -DCMAKE_CXX_FLAGS=-fsanitize=undefined
ninja -C build_w_ubsan
```

Then run the application:
```bash
build_w_ubsan/fct_w_ub -- someNumber
```

If you use a negative number, you should get an error that resembles:
```
$ ./build_w_ubsan/fct_with_ub -- -25
ch10/undefined_behavior/populate_function.cpp:7:17: runtime error: shift exponent -25 is negative
SUMMARY: UndefinedBehaviorSanitizer: undefined-behavior ch10/undefined_behavior/populate_function.cpp:7:17 in 
fctWithUB(-25) == 2519
```

Now, if you run with a number bigger than 31, you should get:
```
$ ./build_w_ubsan/fct_with_ub -- 32
ch10/undefined_behavior/populate_function.cpp:7:17: runtime error: shift exponent 32 is too large for 32-bit type 'int'
```

In both cases, this tells you that at line 7 of `populate.cpp` we are relying on some specific undefined behavior and we should fix that.
