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

#define GMLUA_DOUBLE_API extern "C" __declspec(dllexport) double
#define GMLUA_STRING_API extern "C" __declspec(dllexport) char*

gm::CGMAPI*		gmapi;

GMLUA_DOUBLE_API gmluaInit()
{
	unsigned long result = 0;

	gmapi = gm::CGMAPI::Create(&result);

	// Check the result
	if (result != gm::GMAPI_INITIALIZATION_SUCCESS)
	{
		MessageBox(0, "Unable to initialize GMAPI.", 0, MB_SYSTEMMODAL | MB_ICONERROR);
		return false;
	}

	return true;
}

GMLUA_DOUBLE_API gmluaFree()
{
	gmapi->Destroy();

	return true;
}

GMLUA_DOUBLE_API setErrorScript(double sid)
{
	errorScript = (int)sid;
	return true;
}

GMLUA_DOUBLE_API newFile()
{
	luaFile* f = new luaFile();

	f->lua = lua_open();

	if (!f->lua)
		return false;

	luaL_openlibs(f->lua);

	return (double)(size_t)f;
}

GMLUA_DOUBLE_API registerScript(double i, char* name, double callback)
{
	luaFile* f = (luaFile*)(size_t)i;

	f->addScript(name, (int)callback);

	return true;
}

GMLUA_DOUBLE_API callFunction(double i, char *name, double list)
{
	luaFile* f = (luaFile*)(size_t)i;

	f->call(name, (int)list);

	return true;
}

GMLUA_DOUBLE_API callEvent(double i, char *name, double list)
{
	luaFile* f = (luaFile*)(size_t)i;

	f->call(name, (int)list);

	gm::CGMVariable val = gm::ds_list_find_value((int)list, 0);

	if (val.real() == 1)
		return false;
	else
		return true;
}

GMLUA_DOUBLE_API execute(double i, char* filename)
{
	luaFile* f = (luaFile*)(size_t)i;

	int s = luaL_loadfile(f->lua, filename);
    
	if (s == 0)
	{
		s = lua_pcall(f->lua, 0, LUA_MULTRET, 0);

		if (s != 0)
		{
			_gmError(f->lua);

			return false;
		}

		return true;
	} else {
		return false;
	}
}

GMLUA_DOUBLE_API destroy(double i)
{
	luaFile* f = (luaFile*)(size_t)i;

	lua_close(f->lua);

	delete f;

	return true;
}
