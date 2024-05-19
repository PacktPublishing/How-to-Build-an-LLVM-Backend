```bash
cmake -GNinja -DCMAKE_BUILD_TYPE=Debug -DLLVM_DIR=<path/to/llvm/install>/lib/cmake/llvm -Bbuild .
```

To produce an input:
```bash
clang -o - -S -emit-llvm test.c -O0 | sed -e 's#optnone##g' | <path/to/llvm/build>/bin/opt -S -passes=mem2reg,instnamer > input.ll
```

optnone => remove the attribute that prevents optimizations
mem2reg => get rid of stack accesses / build SSA
instnamer => get rid of the implicit variables

To build:
```bash
ninja -Cbuild
```

To run:
```bash
./build/check_vec_int_ty [input.ll]
```

===
Example for horizontal add

clang -emit-llvm hadd_vector.c -S -o - -O0 | sed -e 's#optnone##g' | <path/to/llvm/build>/bin/opt -S -passes=mem2reg,instnamer
