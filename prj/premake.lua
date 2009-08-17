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
--- build rc-visual
---------------------------------------------------------
package = newpackage()
package.name 		= "rc-facade"
package.kind 		= "exe"
package.language 	= "c++"

package.files = { 
    matchfiles( "../src/*.h", "../src/*.cpp" ),
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

package.links = { "SDL", "SDL_gfx" }
package.config["Debug"].links = { "visualframeworkD", "visualClassesD", "tinyxmlD", "oscpackD" }
package.config["Release"].links = { "visualframework", "visualClassesD", "tinyxml", "oscpack" }

