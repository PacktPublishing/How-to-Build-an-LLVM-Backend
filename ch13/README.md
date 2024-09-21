In this chapter you can discover the transformations performed by some of the optimizations passes.

To see that in action, first setup your build directory:
```bash
cmake -GNinja -DCMAKE_BUILD_TYPE=Debug -DLLVM_DIR=<path/to/llvm/install>/lib/cmake/llvm -Bbuild .
```

Then, when you'll invoke `ninja`, it will run all the passes exercised in this folder.
```bash
ninja -Cbuild
```

This will produce files named `xxx.mir` in the `build` directory.

The output file is produced by stopping the pass pipeline at a specific point:
- `ssa`: before the SSA machine optimization
- `no-phi`: after the PHI elimination pass
- `phys-reg`: after register allocation

In any case, you can see the command used to produce the output by running the `ninja` command with the `-v` option.
