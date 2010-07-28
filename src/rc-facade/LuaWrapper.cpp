/*==============================================================================

	Config.cpp

	rc-facade: a simple 2d graphics engine for the AEC facade
  
	Copyright (C) 2009, 2010  Dan Wilcox <danomatika@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

==============================================================================*/
#include "LuaWrapper.h"

#include "Config.h"

// list of functions to wrap.
static const luaL_Reg functions[] =
{
	{ "background", background },
	{ "stroke", stroke },
	{ "blend", blend },
	{ "noBlend", noBlend },
	{ "rectModeCenter", rectModeCenter },
	{ "rectModeCorner", rectModeCorner },
	{ "wrap", wrap },
	{ "noWrap", noWrap },
	{ "wrapX", wrapX },
	{ "wrapY", wrapY },
	{ "pixel", pixel },
	{ "line", line },
	{ "rect", rect },
	{ "circle", circle },
	{ "getWidth", getWidth },
	{ "getHeight", getHeight },
	{ 0, 0 }
};

//lua_State* LuaWrapper::L = NULL;
bool LuaWrapper::bAbortScript = false;

LuaWrapper::LuaWrapper() : L(NULL), filename(""), bLoaded(false)
{}

LuaWrapper::~LuaWrapper()
{
	closeLuaFile();
}

void LuaWrapper::setLuaFilename(string filename)
{
	this->filename = filename;
}

bool LuaWrapper::loadLuaFile(string filename)
{
	if(filename == "")
		filename = this->filename;
	
	closeLuaFile();
	bLoaded = false;

	L = lua_open();
	if(!L)
	{
		LOG_ERROR << " Error initializing lua" << endl;
		return false;
	}
	
	luaL_openlibs(L);
	//luaopen_debug(L);
	//luaL_register(L, NULL, functions);
	lua_register(L, "stroke", stroke);
	lua_register(L, "rect", rect);
	lua_register(L, "line", line);
	lua_register(L, "getWidth", getWidth);
	lua_register(L, "getHeight", getHeight);
	
	//lua_sethook(L, LuaWrapper::errorHook, LUA_MASKLINE, 0);
	
	this->filename = filename;
	luaL_loadfile(L, this->filename.c_str());
	if(lua_pcall(L, 0, LUA_MULTRET, 0) != 0)
	{
	//	lua_Debug debug;
//		lua_getstack(L, 0, &debug);
//		lua_getinfo(L, "n", &debug);
//		bAbortScript = true;
		LOG_ERROR << " Error running file: " << lua_error(L) << endl;
		closeLuaFile();
		return false;
	}
	bLoaded = true;
	
	return true;
}
		
void LuaWrapper::updateLua()
{
	if(!L)
		return;
	lua_getglobal(L, "update");
	if(lua_pcall(L, 0, 0, 0) != 0)
		lua_error(L);
}

void LuaWrapper::drawLua()
{
	if(!L)
		return;
	lua_getglobal(L, "draw");
	if(lua_pcall(L, 0, 0, 0) != 0)
		lua_error(L);
}

void LuaWrapper::closeLuaFile()
{
	if(L)
	{
		lua_close(L);
		L = NULL;
	}
}

/* ***** PRIVATE ***** */

void LuaWrapper::errorHook(lua_State *L, lua_Debug *ar)
{
	if(ar->event == LUA_HOOKLINE)
	{
		if(bAbortScript)
		{
			lua_pushstring(L, "HookRoutine: Abort requested!");
      		lua_error(L);
		}
	}
}
		
/* ***** FACADE WRAPPER ***** */

int background(lua_State* L)
{
	uint32_t c = (uint32_t) luaL_checkint(L, 1);
	Config::instance().getFacade().setClearColor(c);
	return 0;
}

int stroke(lua_State* L)
{		 
	uint32_t c = (uint32_t) luaL_checkint(L, 1);
	Config::instance().getFacade().stroke(c);
	return 0;
}

int blend(lua_State* L)
{
	Config::instance().getFacade().blend();
	return 0;
}

int noBlend(lua_State* L)
{
	Config::instance().getFacade().noBlend();
	return 0;
}

int rectModeCenter(lua_State* L)
{
	Config::instance().getFacade().rectModeCenter();
	return 0;
}

int rectModeCorner(lua_State* L)
{
	Config::instance().getFacade().rectModeCorner();
	return 0;
}

int wrap(lua_State* L)
{
	Config::instance().getFacade().wrap();
	return 0;
}

int noWrap(lua_State* L)
{
	Config::instance().getFacade().noWrap();
	return 0;
}

int wrapX(lua_State* L)
{
	bool b = luaL_checkint(L, 1);
	Config::instance().getFacade().wrapX(b);
	return 0;
}

int wrapY(lua_State* L)
{
	bool b = luaL_checkint(L, 1);
	Config::instance().getFacade().wrapY(b);
	return 0;
}

int pixel(lua_State* L)
{
	int x = luaL_checkint(L, 1);
	int y = luaL_checkint(L, 2);
	Config::instance().getFacade().pixel(x, y);
	return 0;
}

int line(lua_State* L)
{
	int x1 = luaL_checkint(L, 1);
	int y1 = luaL_checkint(L, 2);
	int x2 = luaL_checkint(L, 3);
	int y2 = luaL_checkint(L, 4);
	Config::instance().getFacade().line(x1, y1, x2, y2);
	return 0;
}

int rect(lua_State* L)
{
	int x = luaL_checkint(L, 1);
	int y = luaL_checkint(L, 2);
	int w = luaL_checkint(L, 3);
	int h = luaL_checkint(L, 4);
	Config::instance().getFacade().rect(x, y, w, h);
	return 0;
}

int circle(lua_State* L)
{
	int x = luaL_checkint(L, 1);
	int y = luaL_checkint(L, 2);
	int r = luaL_checkint(L, 3);
	Config::instance().getFacade().circle(x, y, r);
	return 0;
}

int getWidth(lua_State* L)
{
	lua_pushnumber(L, Config::instance().getFacade().getWidth());
	return 1;
}

int getHeight(lua_State* L)
{
	lua_pushnumber(L, Config::instance().getFacade().getHeight());
	return 1;
}
