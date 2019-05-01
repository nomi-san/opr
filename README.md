# opr
Reduces RAM usage for process on Windows.

### example

```c
#include "opr"

int processId = 123; // -1 for current process
int ret = opr_Clean(processId);
printf("process [%d]: %s\n",
    processId,
    ret == 1 ? "ok" : (ret == -1 ? "cannot access or does not exist" : "fail")
);

```

### multi-lang

List of bindings language:
- Lua: [lopr.c](https://github.com/wy3/opr/tree/main/bindings/lua)
- LuaJIT: [opr.lua](https://github.com/wy3/opr/tree/main/bindings/lua/luajit)
- Python: [opr.py](https://github.com/wy3/opr/tree/main/bindings/python)
