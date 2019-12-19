# opr
Single C/C++ header only that supports reducing process RAM usage.

### platform
- [x] Windows x86 & x64
- [ ] Linux

### example

```c
#include "opr.h"

int processId = 1024; // -1 for current process
int ret = opr_Clean(processId);
printf("process [%d]: %s\n",
    processId,
    ret == 1 ? "ok" : (ret == -1 ? "cannot access or does not exist" : "fail")
);

```

### multiple languages

#### Bindings languages:
- [ ] AutoIt
- [ ] C#
- [ ] Go
- [x] Lua - [lopr.c](https://github.com/wy3/opr/tree/main/bindings/lua) (C library)
- [x] LuaJIT - [opr.lua](https://github.com/wy3/opr/tree/main/bindings/lua/luajit)
- [x] Python - [opr.py](https://github.com/wy3/opr/tree/main/bindings/python)
- [ ] Ruby
- [ ] Rust

#### FFI supports
- Create a new **C** source and add: `#include "opr.h"` (add [DllMain](https://docs.microsoft.com/en-us/windows/desktop/dlls/dllmain) if necessary)
- Build as *dynamic library/DLL* with preprocessor: `OPR_EXPORTS` or `BUILD_DLL`
```
$ gcc -w -shared -O2 -o opr.dll -DBUILD_DLL src.c -lpsapi
```
