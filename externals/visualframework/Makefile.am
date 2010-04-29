# visualframework

# dirs to delve into
SUBDIRS = vmmlib

# the library to build, dont install just link to execs
noinst_LIBRARIES = libvisualframework.a

# libs sources, headers here because we dont want to install them
libvisualframework_a_SOURCES = \
        visualframework.h \
        Application.h \
        Application.cpp \
            graphics/Color.h \
            graphics/Font.h \
            graphics/Font.cpp \
            graphics/Graphics.h \
            graphics/Graphics.cpp \
            graphics/Image.h \
            graphics/Image.cpp \
            graphics/resize/resize++.h \
            graphics/resize/resize++.cpp \
            graphics/sprig/sprig.h \
            graphics/sprig/sprig_inline.h \
            graphics/sprig/sprig_common.h \
            graphics/sprig/SPG_misc.c \
            graphics/sprig/SPG_polygon.c \
            graphics/sprig/SPG_primitives.c \
            graphics/sprig/SPG_rotation.c \
            graphics/sprig/SPG_surface.c \
        Common.h \
        Exception.h \
        Log.h \
            net/Net.h \
            net/Net.cpp \
            net/UdpListener.h \
            net/UdpListener.cpp \
            net/UdpSender.h \
            net/UdpSender.cpp \
        Point.h \
        Point.cpp \
        Thread.h \
        Thread.cpp \
        Timer.h

# include paths
AM_CPPFLAGS = $(CXXFLAGS) -I./ -I../ \
			  $(SDL_CFLAGS) $(SDL_gfx_CFLAGS) $(SDL_NET_CFLAGS) $(SDL_TTF_CFLAGS) $(SDL_image_CFLAGS)


# libs to link
AM_LDFLAGS = $(SDL_LIBS) $(SDL_gfx_LIBS) $(SDL_NET_LIBS) $(SDL_TTF_LIBS) $(SDL_image_LIBS)

