
# load externals variables
include $(top_srcdir)/externals/externals.mk

# the library to build, dont install just link to execs
noinst_LIBRARIES = libcommon.a

# bin sources, headers here because we dont want to install them
dist_libcommon_a_SOURCES = Facade.h Facade.cpp

# include paths
AM_CPPFLAGS =  $(CXXFLAGS) $(SDL_CFLAGS) -I$(top_srcdir)/src $(EXTERNALS_CFLAGS)

# libs to link
AM_LDFLAGS = $(SDL_LIBS) $(SDL_GFX_LIBS) $(SDL_NET_LIBS) $(SDL_image_LIBS) \
			 -L$(top_builddir)/src/facade -lfacade $(EXTERNALS_LIBS)

