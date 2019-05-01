#include "opr.h"
#include "lua.h"
#include "lauxlib.h"

static int lopr_Clean(lua_State *L)
{
	int ret;

	if (lua_isnumber(L, 1))
	{
		int pid = lua_tointeger(L, 1);
		ret = opr_Clean(pid);
	}
	else if	(lua_isstring(L, 1))
	{
		const char *pname = lua_tostring(L, 1);
		ret = opr_CleanByName(pname);
	}
	else if (lua_isnoneornil(L, 1))
	{
		int pid = lua_tointeger(L, -1);
		ret = opr_Clean(pid);
	}

	lua_pushinteger(L, ret);
	return 1;
}

static int lopr_CleanAll(lua_State *L)
{
	int count = opr_CleanAll();

	lua_pushinteger(L, count);
	return 1;
}

__declspec(dllexport)
int luaopen_opr(lua_State *L)
{
	lua_newtable(L);

	lua_pushcfunction(L, lopr_Clean);
	lua_setfield(L, -2, "Clean");

	lua_pushcfunction(L, lopr_CleanAll);
	lua_setfield(L, -2, "CleanAll");

	return 1;
}