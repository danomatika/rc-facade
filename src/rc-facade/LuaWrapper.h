/*==============================================================================

	LUA_WRAPPER.h

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
#ifndef LUA_WRAPPER_H
#define LUA_WRAPPER_H

#include "Common.h"

#include <lua.hpp>

class LuaWrapper
{
	public:

		LuaWrapper();
		virtual ~LuaWrapper();
		
		// set the filename, dosen't load
		void setLuaFilename(string filename);
		
		// load a lua script to run, closes existing script
		// uses existing filename if filename = ""
		bool loadLuaFile(string filename="");
		
		// script callbacks
		void updateLua();
		void drawLua();
		
		// close if a file is open
		void closeLuaFile();
		
		/// get the current filename
		inline string getLuaFilename() {return filename;}
	
	private:
	
		static void errorHook(lua_State *L, lua_Debug *ar);
	
		string filename;
		lua_State* L;
		bool bLoaded;
		
		static bool bAbortScript;	// should the script be aborted?
};

		/* ***** FACADE WRAPPER ***** */
		
		static int background(lua_State* L);
		
		static int stroke(lua_State* L);
		
		static int blend(lua_State* L);
		static int noBlend(lua_State* L);
		
		static int rectModeCenter(lua_State* L);
        static int rectModeCorner(lua_State* L);
		
		static int wrap(lua_State* L);
        static int noWrap(lua_State* L);
        static int wrapX(lua_State* L);
        static int wrapY(lua_State* L);

        static int pixel(lua_State* L);
        static int line(lua_State* L);
        static int rect(lua_State* L);
        static int circle(lua_State* L);
		
		static int getWidth(lua_State* L);
        static int getHeight(lua_State* L);

#endif // LUA_WRAPPER_H
