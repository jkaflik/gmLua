#define luaStart
global.f_lua_dll = "gmLua.dll";

global.f_lua_seterrorscript = external_define(global.f_lua_dll, "setErrorScript", dll_cdecl, ty_real, 1, ty_real);
global.f_lua_register       = external_define(global.f_lua_dll, "registerScript", dll_cdecl, ty_real, 3, ty_real, ty_string, ty_real);
global.f_lua_event          = external_define(global.f_lua_dll, "callEvent", dll_cdecl, ty_real, 3, ty_real, ty_string, ty_real);
global.f_lua_call           = external_define(global.f_lua_dll, "callFunction", dll_cdecl, ty_real, 3, ty_real, ty_string, ty_real);
global.f_lua_load           = external_define(global.f_lua_dll, "loadFile", dll_cdecl, ty_real, 2, ty_real, ty_string);
global.f_lua_destroy        = external_define(global.f_lua_dll, "destroyState", dll_cdecl, ty_real, 1, ty_real);
global.f_lua_new            = external_define(global.f_lua_dll, "newState", dll_cdecl, ty_real, 0);
global.f_lua_addinternal    = external_define(global.f_lua_dll, "addInternal", dll_cdecl, ty_real, 1, ty_real);

return external_call(external_define(global.f_lua_dll, "gmluaInit", dll_cdecl, ty_real, 0));


#define luaEnd
external_call(external_define(global.f_lua_dll, "gmluaFree", dll_cdecl, ty_real, 0));

#define luaNew
return external_call(global.f_lua_new);

#define luaDestroy
return external_call(global.f_lua_destroy, argument0);

#define luaRegister
return external_call(global.f_lua_register, argument0, argument1, argument2);

#define luaLoadFile
return external_call(global.f_lua_load, argument0, argument1);

#define luaEvent
var list, ret;

list = ds_list_create();

for (i = 0; i <= argument2; i += 1)
    ds_list_add(list, argument[3 + i]);

ret = external_call(global.f_lua_event, argument0, argument1, list);

ds_list_destroy(list);

return ret;


#define luaCall
var list, ret;

list = ds_list_create();

for (i = 0; i <= argument2; i += 1)
    ds_list_add(list, argument[3 + i]);

external_call(global.f_lua_call, argument0, argument1, list);

ret = ds_list_find_value(list, 0);

ds_list_destroy(list);

return ret;


#define luaSetErrorScript
return external_call(global.f_lua_seterrorscript, argument0);

#define luaAddInternal
external_call(global.f_lua_addinternal, argument0);

