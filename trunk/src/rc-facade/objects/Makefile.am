# objects

# load externals variables
include $(top_srcdir)/externals/externals.mk

# the library to build, dont install just link to execs
noinst_LIBRARIES = libobjects.a

# libs sources, headers here because we dont want to install them
libobjects_a_SOURCES = \
        Bitmap.h Bitmap.cpp \
        DrawableObject.h \
        Image.h Image.cpp \
        Line.h \
        Objects.h \
        Pixel.h Rect.h \
        Sprite.h Sprite.cpp

# include paths
AM_CPPFLAGS = $(CXXFLAGS) $(SDL_CFLAGS) $(EXTERNALS_CFLAGS)


# libs to link
AM_LDFLAGS = $(SDL_LIBS) $(SDL_GFX_LIBS) $(SDL_NET_LIBS) $(EXTERNALS_LIBS)
