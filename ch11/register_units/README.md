Example of regunit
cmake -GNinja -DCMAKE_BUILD_TYPE=Debug -DLLVM_DIR=<path/to/llvm/install>/lib/cmake/llvm/ -Bbuild .

TODO: describe what needs to be done: look at yourTurn-reginfo.td
+ cmds to run and test
Command to run:
ninja -C build
./build/print_regunit
