In this chapter you can discover the transformations performed by some of the optimizations passes.

To see that in action, first setup your build directory:
```bash
cmake -GNinja -DCMAKE_BUILD_TYPE=Debug -DLLVM_DIR=<path/to/llvm/install>/lib/cmake/llvm -Bbuild .
```

Then, when you'll invoke `ninja`, it will run all the passes exercised in this folder.
```bash
ninja -Cbuild
```

This will produce files named `xxx.out.ll` in the `build` directory.

For each `xx.out.ll` file, you'll find the input IR in this chapter's directory with the name `xx.ll`.
For instance, the input IR of `dce.out.ll` is `dce.ll`.

The output file is produced by applying the pass with the same name as the input file to the input file.
E.g., we apply the `dce` pass to the `dce.ll` input file to produce `dce.out.ll`.

A few files do not follow this convention.
These are `xor.ll`, `canonical_form.ll`, and `value_tracking.ll`.
All three files exercises `instcombine`.

In any case, you can see the command used to produce the output by running the `ninja` command with the `-v` option.

Also if you want to rerun one (or several) passes, you can just modify the related input IR file (e.g., by using `touch xx.ll`) and rerun the Ninja command.

For this chapter, look at the differences between the input and output IRs to see what happened.
You can for instance use the following command:
```bash
diff -U10 xx.ll build/xx.out.ll
```
