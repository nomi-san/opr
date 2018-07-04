#include <windows.h>
#include "lua.h"
#include "lapi.h"
#include "lauxlib.h"

typedef BOOL(__stdcall * EmptyWorkingSet)(HANDLE);

static int l_OpenProcess(lua_State* L)
{
	lua_pushinteger(L, 
		(int)OpenProcess(
			luaL_checkinteger(L, 1),
			luaL_checkinteger(L, 2),
			luaL_checkinteger(L, 3)
		));
	return 1;
}

static int l_EmptyWorkingSet(lua_State* L)
{
	HMODULE module = LoadLibraryA("psapi.dll");
	FARPROC proc = GetProcAddress(module, "EmptyWorkingSet");
	lua_pushinteger(L,
		((EmptyWorkingSet)proc)(
			(HANDLE)luaL_checkinteger(L, 1)
		));
	return 1;
}

static int l_CloseHandle(lua_State* L)
{
	lua_pushinteger(L,
		CloseHandle(
			(HANDLE)luaL_checkinteger(L, 1)
	));
	return 1;
}

int __declspec(dllexport) luaopen_module(lua_State* L)
{
	lua_register(L, "OpenProcess", l_OpenProcess);
	lua_register(L, "EmptyWorkingSet", l_EmptyWorkingSet);
	lua_register(L, "CloseHandle", l_CloseHandle);
	return 1;
}
