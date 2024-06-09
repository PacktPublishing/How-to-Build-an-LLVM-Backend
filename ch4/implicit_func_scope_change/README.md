```bash
cmake -GNinja -DCMAKE_BUILD_TYPE=Debug -DLLVM_DIR=<path/to/llvm/install>/lib/cmake/llvm -Bbuild .
ninja -Cbuild
./build/implicit_change_of_scope
```

