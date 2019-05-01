# opr
**Single C/C++** header that supports **reducing RAM usage** for process on Windows.

### example

```c
#include "opr.h"

int processId = 123; // -1 for current process
int ret = opr_Clean(processId);
printf("process [%d]: %s\n",
    processId,
    ret == 1 ? "ok" : (ret == -1 ? "cannot access or does not exist" : "fail")
);

```

### multi-lang

List of bindings language:
- [ ] AutoIt
- [ ] Go
- [x] Lua - [lopr.c](https://github.com/wy3/opr/tree/main/bindings/lua) (C library)
- [x] LuaJIT - [opr.lua](https://github.com/wy3/opr/tree/main/bindings/lua/luajit)
- [x] Python - [opr.py](https://github.com/wy3/opr/tree/main/bindings/python)
- [ ] Ruby
- [ ] Rust
