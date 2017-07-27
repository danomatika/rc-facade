rc-facade
===================================

a 2d framebuffer lib and tools for the Ars Electronica Center media facade

Copyright (c) [Dan Wilcox](danomatika.com) 2009, 2010

The libfacade library is licensed under the [MIT License](http://www.opensource.org/licenses/mit-license.php)

The rc-facade & facade-simulator tools are licensed under the [GNU GPL v3](http://www.gnu.org/licenses/gpl.html)

DESCRIPTION
-----------

rc-facade is an unofficial set of tools for graphics on the led facade of the [Ars Electronica](http://www.aec.at/center_about_en.php).

The rc-facade package contains the following parts:

1. libfacade - 2d framebuffer, builds UDP packets
2. rc-facade - osc-controlled, 2d framebuffer engine
3. facade-simulator - osc command tool

This group of tools allows any OSC ([Open Sound Control](http://en.wikipedia.org/wiki/Open_Sound_Control)) capable program to control simple 2d visuals which are specified in xml scene descriptions. The library presents the facade as a 2d drawing surface and builds UDP packets with the correct window addresses. These tools have been tested with the official simulator from the  [Ars Electronica Futurelab](http://new.aec.at/futurelab/en) but are not affiliated with or supported by the Futurelab.

These tools were developed as part of the [robotcowboy project](http://robotcowboy.com) for the ["Close Encounters of the Bit Kind"](http://vimeo.com/7741821) performance during the Ars Electronica Festival 2009.

BUILD REQUIREMENTS
------------------

The following libraries are required to build the tools (rc-facade & facade-simulator):

* SDL
* SDL_gfx
* SDL_net
* SDL_ttf
* SDL_image
* liblo (lightweight osc lib)

As this is an autootols project, it should be possible to compile it on Mac, Linux, and Windows.

### LINUX

Not tested as of yet. Should be possible if you install the libraries.

### MAC OS OX

On Mac OS X, they can be installed using macports (http://macports.org) or homebrew (http://brew.sh)

* install the macport binary and setup the macports environment
* goto the Terminal and install the libs:
<pre>
sudo port install libsdl libsdl_gfx libsdl_net libsdl_ttf libsdl_image liblo
</pre>

If using macports on Mac OS X, you need to set the macports include and lib dirs before running ./configure:
<pre>
export CPPFLAGS=-I/opt/local/include && export LDFLAGS=-L/opt/local/lib
</pre>

### Windows

Not tested as of yet. Should be possible using cygwin or minigw, building/installing the libraries, and adding the lib paths.


BUILD AND INSTALLATION
----------------------

As this is an GNU autotools project, simply run:

<pre>
./configure
make
sudo make install
</pre>

By default, the configure script installs to `/usr/local`.  To change this behavior, specify a new dir before building the project:

<pre>
./configure --prefix=/path/to/install/dir
</pre>

If using macports on Mac OS X, it is recommended to use the macports default prefix of `/opt/local`.

USAGE
-----

All applications have a full help usage printout, use -h or --help.

----

[1]:https://raw.github.com/danomatika/rc-facade/master/doc/rc-facade_screenshot.png

![image][1]

    % rc-facade scene_file.xml

Starts rc-visual using the given xml scene description. The file sets connection information (if not using defaults) and lists visual scenes and scene elements. Look at the example.xml file install to the doc folder for details.

See the pd patches in the pd folder for info on how to communicate with rc-viusal.

Note: Values set on the commandline override those in the scene file.

----

    % facade-simulator

A test destination for facade UDP packets. Displays framebuffer at the 25 fps refresh rate of the actual AEC hardware.

DEVELOPING
----------

A Premake4 script and IDE files can be found in the prj folder.  Premake4 can generate the IDE files from a given lua script.  Download Premake4 from http://industriousone.com/premake.

Make sure the externals are built by calling the prj/setupbuild script which runs configure and calls make in the externals dir.

You can enable a debug build using:
<pre>
./configure --enable-debug
</pre>

I develop using an IDE, then update the autotools files when the sources are finished.  I run make dist-check to make sure the distributable package can be built successfully.

