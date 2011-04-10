/************************************************************************** 
  LICENSE:

    gmLua is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    GMAPI is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with GMAPI; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
    02110-1301 USA
***************************************************************************/

#include "gmlua.h"

int errorScript;

luaFile::luaFile()
{

}

void luaFile::addScript(std::string name, int callback)
{
	lua_pushnumber(lua, callback);
	lua_pushcclosure(lua, _gmCall, 1);
	lua_setglobal(lua, name.c_str());
}

void luaFile::call(char *name, int list)
{
	lua_getglobal(lua, name);
	int argc = gm::ds_list_size(list);

	if (argc > 0)
	{
		for (int n = 0; n < argc; n++)
		{
			gm::CGMVariable val = gm::ds_list_find_value(list, n);

			if (val.IsString())
			{
				lua_pushstring(lua, val.c_str());
			} else {
				lua_pushnumber(lua, val.real());
			}
		}
	}

	int s = lua_pcall(lua, argc, 1, 0);

	if (s != 0)
	{
		_gmError(lua);
	} else {
		gm::ds_list_clear(list);

		if (lua_type(lua, -1) == LUA_TSTRING)
		{
			gm::ds_list_add(list, lua_tostring(lua, -1));
		} else {
			gm::ds_list_add(list, lua_tonumber(lua, -1));
		}
	  
		lua_pop(lua, 1);
	}
}

int _gmCall(lua_State* L)
{
	lua_pushvalue(L, lua_upvalueindex(1));
	int argc = lua_gettop(L) - 1;
	int callback = (int)lua_tonumber(L, argc + 1);

	gm::CGMVariable* arg = new gm::CGMVariable[argc];

	for (int i = 0; i <= argc - 1; i++)
	{
		if (lua_type(L, i + 1) == LUA_TSTRING)
		{
			arg[i] = lua_tostring(L, i + 1);
		} else if (lua_type(L, i + 1) == LUA_TNUMBER) {
			arg[i] = lua_tonumber(L, i + 1);
		}
	}

	gm::CGMVariable result = gm::script_execute(callback, arg, argc);

	delete[] arg;

	if (result.IsString())
	{
		lua_pushstring(L, result.c_str());
	} else {
		if (result.real() == 0)
			return 0;

		lua_pushnumber(L, result.real());
	}

	return 1;
}

void _gmError(lua_State* L)
{
	if (errorScript >= 0)
	{
		gm::CGMVariable arg = lua_tostring(L, -1);
		gm::script_execute(errorScript, &arg, 1);
	}
	
	lua_pop(L, 1);
}

