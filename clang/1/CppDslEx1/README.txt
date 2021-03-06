This is a simple example demonstrating how to use clang's facility for
providing AST consumers using a plugin.

Build the plugin by running `make` in this directory.

Once the plugin is built, you can run it using:
--
Linux:
$ <llvm-build-path>/bin/clang++ -Xclang -load -Xclang <llvm-build-path>/lib/CppDslEx1.so -Xclang -add-plugin -Xclang ex1-act -Xclang -emit-llvm -S input.cpp -o -
for example:
  ~/llvm/10.0.0/release/build-cb/bin/clang++ -Xclang -load -Xclang /home/czs/llvm/10.0.0/release/build-cb/lib/CppDslEx1.so -Xclang -add-plugin -Xclang ex1-act -Xclang -ast-dump -fsyntax-only input.cpp -o -
