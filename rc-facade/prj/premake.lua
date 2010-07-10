--[[
	
	Dan Wilcox <danomatika@gmail.com>

--]]

project.name 		= "rc-facade"
project.bindir	 	= "../bin"
project.libdir 		= "../lib"

project.configs		= { "Debug", "Release" }

---------------------------------------------------------
--- build the externals
---------------------------------------------------------
package = newpackage()
package.name 		= "externals"
package.kind 		= "lib"
package.language 	= "c++"

package.postbuildcommands = {
	"cd ../externals/visualframework/prj && make"
}

---------------------------------------------------------
--- build the facade lib
---------------------------------------------------------
package = newpackage()
package.name 		= "facade"
package.kind 		= "lib"
package.language 	= "c++"

package.files = { 
    matchfiles( "../src/facade/*.h",
    			"../src/facade/*.cpp")
}

package.includepaths = {
	"../src",
    "/usr/include",
	"../externals/visualframework/src",
	"../externals/visualframework/externals",
	"../externals/visualframework/externals/include"
}

package.libpaths = {
	"../lib",
	"../externals/visualframework/lib",
	"../externals/visualframework/externals/lib",
    "/usr/lib"
}

package.config["Debug"].objdir   = "../obj/facade/Debug"
package.config["Release"].objdir = "../obj/facade/Release"

package.config["Debug"].target   = "facadeD"
package.config["Release"].target = "facade"

package.defines                   = { "LINUX" };
package.config["Debug"].defines   = { "DEBUG", "_DEBUG" };
package.config["Release"].defines = { "NDEBUG" };

package.buildflags                   = { "extra-warnings" }
package.buildoptions                 = { "-Wno-unknown-pragmas" }
package.config["Debug"].buildoptions = { "-ggdb" }

package.links = { "SDL", "SDL_gfx", "SDL_net" }
package.config["Debug"].links = { "visualframeworkD", "tinyxmlD", "oscpackD" }
package.config["Release"].links = { "visualframework", "tinyxml", "oscpack" }

---------------------------------------------------------
--- build rc-visual
---------------------------------------------------------
package = newpackage()
package.name 		= "rc-facade"
package.kind 		= "exe"
package.language 	= "c++"

package.files = { 
    matchfiles( "../src/*.h",
    			"../src/*.cpp",
    			"../src/objects/*.h",
    			"../src/objects/*.cpp")
}

package.includepaths = {
	"../src",
    "/usr/include",
	"../externals/visualframework/src",
	"../externals/visualframework/externals",
	"../externals/visualframework/externals/include"
}

package.libpaths = {
	"../lib",
	"../externals/visualframework/lib",
	"../externals/visualframework/externals/lib",
    "/usr/lib"
}

package.config["Debug"].objdir   = "../obj/rc-facade/Debug"
package.config["Release"].objdir = "../obj/rc-facade/Release"

package.config["Debug"].target   = "rc-facadeD"
package.config["Release"].target = "rc-facade"

package.defines                   = { "LINUX" };
package.config["Debug"].defines   = { "DEBUG", "_DEBUG" };
package.config["Release"].defines = { "NDEBUG" };

package.buildflags                   = { "extra-warnings" }
package.buildoptions                 = { "-Wno-unknown-pragmas" }
package.config["Debug"].buildoptions = { "-ggdb" }

package.links = { "SDL", "SDL_gfx", "SDL_net", "SDL_image" }
package.config["Debug"].links = { "facadeD", "visualframeworkD", "tinyxmlD", "oscpackD" }
package.config["Release"].links = { "facade", "visualframework", "tinyxml", "oscpack" }

