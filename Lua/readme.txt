Build module:

- for GCC
gcc -shared -o module.dll module.c -I%lua%/src -L%lua%/lib -Llua

- for TCC:
tcc -impdef %lua%/bin/lua.dll
tcc -shared -o module.dll module.c -I%lua%/src lua.def

Run:
lua main.lua
