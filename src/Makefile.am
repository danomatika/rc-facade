# rc-facade

# go into these dirs and process makefiles
SUBDIRS = facade objects

# load externals variables
include $(top_srcdir)/externals/externals.mk

# programs to build
bin_PROGRAMS = rc-facade

# bin sources, headers here because we dont want to install them
rc_facade_SOURCES = \
        Common.h Config.h Config.cpp \
        FacadeApp.h FacadeApp.cpp \
        main.cpp \
        Scene.h Scene.cpp \
        SceneManager.h SceneManager.cpp

# include paths
rc_facade_CPPFLAGS = $(CXXFLAGS) $(SDL_CFLAGS) $(EXTERNALS_CFLAGS)

# local libs to link
rc_facade_LDADD = facade/libfacade.a objects/libobjects.a

# libs to link
rc_facade_LDFLAGS = $(SDL_LIBS) $(SDL_GFX_LIBS) $(SDL_NET_LIBS) $(EXTERNALS_LIBS)
