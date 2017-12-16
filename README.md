# Project is deprecated

Features
--------
  * Call GM functions and scripts from Lua scripts (thanks to GMAPI)
  * Call Lua functions from GM
  * Simple events system

Look above for download!

How to compile
--------------
You can compile gmLua yourself. It depends on two libraries: *GMAPI* and *Lua5*.

GMAPI is written by a Polish programmer, Snake, you can download it ( http://gmc.yoyogames.com/index.php?showtopic=429267 ). It allows you to interact with GM from C++.

You can download the Lua binaries: http://gmlua.googlecode.com/files/lua5_1_4_Win32_dll8_lib.zip.
gmLua is developed and compiled with Microsoft Visual C++ 2008, the source includes a project file.
Please note, that gmLua is currently unavailable on Game Maker OS X version, because GMAPI doesn't work on these OS.

Example Usage
=============
In GML
------
    luaStart();

    lua = luaNew();

    if(!lua)
    {
        show_error("Failed to create Lua state.", true);
    }

    luaRegister(lua, "showMessage", showMessage);
    luaLoadFile(lua, get_string("Type your Lua script path (default: game.lua)", "game.lua"));
    luaEvent(lua, "onCreate", 1, id);
    
In Lua
------
    function onCreate(id) -- onCreate, called from GML.
	    showMessage("ID: " .. tostring(id))
    end    

TODO
====
 * Redo registering GM functions

Changelog
=========
v0.4
----
* finished new system for calling GM functions

v0.3
----
* redid most of the DLL
* removed calling of GM function temporarily, new method being thought of

v0.2
----
* renamed GM scripts
* support for registering default GM functions
* added luaCall function which make able to call Lua function
* rewritten code
* some bug fixed
* usage of new GMAPI
 
Credits
=======
 * Jakub Kaflik (http://kofel.pl/)
 * kthxbairohan
