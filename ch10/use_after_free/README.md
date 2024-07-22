# Easily find memory corruption #

In this exercise you need to leverage the address sanitizer to find what is wrong with the `buggyBuildModule` function implemented in `populate_function.cpp`.

Build the code using the steps below.

Run it and observe the crash.

Now, think how you can find this crash easily.

Bonus: Fix the crash!

You can look at `ch3/build_ir` for a correct way of doing the `buildModule` implementation.

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
./build/use_after_free
```

This will run the buggy build module implementation.

At this point it should crash.

## Solution ##

Configure your build with address sanitizer enabled and build:
```bash
cmake -GNinja -DCMAKE_BUILD_TYPE=Debug -DLLVM_DIR=<path/to/llvm/install>/lib/cmake/llvm -Bbuild_w_asan . -DCMAKE_CXX_FLAGS=-fsanitize=address
ninja -C build_w_asan
```

Then run the application:
```bash
build_w_asan/use_after_free
```

And you should see an output resembling:
```
=================================================================
==37427==ERROR: AddressSanitizer: heap-use-after-free on address 0x000108f03ca0 at pc 0x000105baf828 bp 0x00016b1a6830 sp 0x00016b1a5ff0
READ of size 15 at 0x000108f03ca0 thread T0
    #0 0x105baf824 in wrap_memchr+0x27c (libclang_rt.asan_osx_dynamic.dylib:arm64e+0x1b824)
    #1 0x1945b7cac in std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>>::find(char, unsigned long) const+0x38 (libc++.1.dylib:arm64e+0x1bcac)
    #2 0x104d3c968 in llvm::Module::print(llvm::raw_ostream&, llvm::AssemblyAnnotationWriter*, bool, bool) const+0x9b0 (use_after_free:arm64+0x1000e4968)
    #3 0x104c5a088 in main main.cpp:18
    #4 0x1942fe0dc  (<unknown module>)

0x000108f03ca0 is located 160 bytes inside of 752-byte region [0x000108f03c00,0x000108f03ef0)
freed by thread T0 here:
    #0 0x105bf5b8c in wrap__ZdlPv+0x74 (libclang_rt.asan_osx_dynamic.dylib:arm64e+0x61b8c)
    #1 0x104e836f4 in llvm::LLVMContextImpl::~LLVMContextImpl()+0xf4 (use_after_free:arm64+0x10022b6f4)
    #2 0x104e81910 in llvm::LLVMContext::~LLVMContext()+0x18 (use_after_free:arm64+0x100229910)
    #3 0x104c5cab4 in buggyBuildModule() populate_function.cpp:152
    #4 0x104c59fc8 in main main.cpp:11
    #5 0x1942fe0dc  (<unknown module>)

previously allocated by thread T0 here:
    #0 0x105bf574c in wrap__Znwm+0x74 (libclang_rt.asan_osx_dynamic.dylib:arm64e+0x6174c)
    #1 0x104c5ce78 in std::__1::__unique_if<llvm::Module>::__unique_single std::__1::make_unique[abi:ue170006]<llvm::Module, char const (&) [16], llvm::LLVMContext&>(char const (&) [16], llvm::LLVMContext&) unique_ptr.h:689
    #2 0x104c5b394 in buggyBuildModule() populate_function.cpp:71
    #3 0x104c59fc8 in main main.cpp:11
    #4 0x1942fe0dc  (<unknown module>)

SUMMARY: AddressSanitizer: heap-use-after-free (libclang_rt.asan_osx_dynamic.dylib:arm64e+0x1b824) in wrap_memchr+0x27c
Shadow bytes around the buggy address:
  0x000108f03a00: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x000108f03a80: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x000108f03b00: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x000108f03b80: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
  0x000108f03c00: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
=>0x000108f03c80: fd fd fd fd[fd]fd fd fd fd fd fd fd fd fd fd fd
  0x000108f03d00: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x000108f03d80: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x000108f03e00: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd fd
  0x000108f03e80: fd fd fd fd fd fd fd fd fd fd fd fd fd fd fa fa
  0x000108f03f00: fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa fa
Shadow byte legend (one shadow byte represents 8 application bytes):
  Addressable:           00
  Partially addressable: 01 02 03 04 05 06 07 
  Heap left redzone:       fa
  Freed heap region:       fd
  Stack left redzone:      f1
  Stack mid redzone:       f2
  Stack right redzone:     f3
  Stack after return:      f5
  Stack use after scope:   f8
  Global redzone:          f9
  Global init order:       f6
  Poisoned by user:        f7
  Container overflow:      fc
  Array cookie:            ac
  Intra object redzone:    bb
  ASan internal:           fe
  Left alloca redzone:     ca
  Right alloca redzone:    cb
==37427==ABORTING
Abort trap: 6
```

What this tells you is that at line 18 of `main.cpp` we are using an object that has been deallocated at line 152 of `populate_function.cpp`.

Furthermore, it tells us that this object was freed with `~LLVMContext`, i.e., the destructor of the LLVMContext.

Therefore the problem here is that our LLVMContext does not have the proper scope.

Indeed it is local to `buggyBuildModule`, whereas its live-range must out-live its Module, which in this case goes beyond `buggyBuildModule`.
