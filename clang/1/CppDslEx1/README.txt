This is a simple example demonstrating how to use clang's facility for
providing AST consumers using a plugin.

Build the plugin by running `make` in this directory.

Once the plugin is built, you can run it using:
--
Linux:
$ <llvm-build-path>/bin/clang++ -Xclang -load -Xclang <llvm-build-path>/lib/CppDslEx1.so -Xclang -add-plugin -Xclang ex1-act -Xclang -emit-llvm -S input.cpp -o -
for example:
  ~/llvm/debug/build/bin/clang++ -Xclang -load -Xclang /home/cschen/llvm/debug/build/lib/CppDslEx1.so -Xclang -add-plugin -Xclang ex1-act -Xclang -ast-dump -fsyntax-only input.cpp -o -
