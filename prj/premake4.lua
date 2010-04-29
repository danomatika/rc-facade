--[[ A solution contains projects, and defines the available configurations

http://industriousone.com/premake/user-guide

example: http://opende.svn.sourceforge.net/viewvc/opende/trunk/build/premake4.lua?revision=1708&view=markup

http://bitbucket.org/anders/lightweight/src/tip/premake4.lua

]]
solution "rc-facade"
	configurations { "Debug", "Release" }
	objdir "../obj"
 
-- convenience library
project "facade"
	kind "StaticLib"
	language "C++"
	targetdir "../lib"
	files { "../src/facade/**.h", "../src/facade/**.cpp" }
	
	includedirs { "../src",
				  "../externals/",
				  "../externals/visualframework",
			 	  "../externals/xmlframework",
			  	  "../externals/oscframework" }
	libdirs { "../externals/visualframework" }
    links { "visualframework", "SDL_net" }
	
	configuration "linux"
		buildoptions { "`pkg-config --cflags sdl`",
					   "`pkg-config --cflags SDL_gfx`",
					   "`pkg-config --cflags SDL_image`" }
		linkoptions { "`pkg-config --libs sdl`",
					  "`pkg-config --libs SDL_gfx`",
					  "`pkg-config --libs SDL_image`" }
	
	configuration "macosx"
		-- get rid of visibilty warnings
		buildoptions { "-fvisibility-inlines-hidden" }
		-- MacPorts
		includedirs { "/opt/local/include" }
		libdirs { "/opt/local/lib" }

	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols" }

	configuration "Release"
		defines { "NDEBUG" }
		flags { "Optimize" } 

-- rc-unit executable
project "rc-facade"
	kind "ConsoleApp"
	language "C++"
	targetdir "../bin"
	files { "../src/rc-facade/**.h", "../src/rc-facade/**.cpp" }
	
	includedirs { "../src",
				  "../externals/",
				  "../externals/visualframework",
			 	  "../externals/xmlframework",
			  	  "../externals/oscframework" }
	libdirs { "../externals/visualframework",
			  "../externals/xmlframework",
      		  "../externals/oscframework" }
	links { "facade", "oscframework", "xmlframework", "visualframework",
		    "SDL_net", "SDL_ttf" }

	configuration "linux"
		buildoptions { "`pkg-config --cflags sdl`",
					   "`pkg-config --cflags SDL_gfx`",
					   "`pkg-config --cflags liblo`",
					   "`pkg-config --cflags SDL_image`" }
		linkoptions { "`pkg-config --libs sdl`",
					  "`pkg-config --libs SDL_gfx`",
					  "`pkg-config --libs liblo`",
					  "`pkg-config --libs SDL_image`" }

	configuration 'macosx'
		-- MacPorts
		includedirs { "/opt/local/include"}
		libdirs { "/opt/local/lib" }
		links { "lo", "pthread", "SDLmain", "SDL", "SDL_gfx" }
		linkoptions { "-Wl,-framework,Cocoa", "-Wl,-framework,OpenGL",
					  "-Wl,-framework,ApplicationServices",
					  "-Wl,-framework,Carbon", "-Wl,-framework,AudioToolbox",
					  "-Wl,-framework,AudioUnit", "-Wl,-framework,IOKit" }

	configuration "Debug"
		defines { "DEBUG" }
		flags { "Symbols" }

	configuration "Release"
		defines { "NDEBUG" }
		flags { "Optimize" }
		
