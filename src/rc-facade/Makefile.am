# rc-facade

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
        SceneManager.h SceneManager.cpp \
        objects/Bitmap.h \
        objects/Bitmap.cpp \
        objects/DrawableObject.h \
        objects/Line.h \
        objects/Objects.h \
        objects/Pixel.h \
        objects/Rect.h \
        objects/Sprite.h \
        objects/Sprite.cpp
        
#        objects/Image.h 
#        objects/Image.cpp 

# include paths
rc_facade_CPPFLAGS = $(CXXFLAGS) $(SDL_CFLAGS) $(EXTERNALS_CFLAGS) \
					-I$(top_srcdir)/src

# local libs to link
rc_facade_LDADD = -L$(top_builddir)/src/facade -lfacade $(EXTERNALS_LIBS)
#				  $(top_builddir)/rc-facade/objects/libobjects.a

# libs to link
rc_facade_LDFLAGS = $(SDL_LIBS) $(LO_LIBS) $(SDL_GFX_LIBS) $(SDL_NET_LIBS)
