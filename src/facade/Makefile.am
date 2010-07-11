# facade

# load externals variables
include $(top_srcdir)/src/externals/externals.mk

# the library to build, dont install just link to execs
noinst_LIBRARIES = libfacade.a

# libs sources, headers here because we dont want to install them
dist_libfacade_a_SOURCES = \
        Building.h \
        Facade.h Facade.cpp \
        FrameBuffer.h FrameBuffer.cpp \
        Side.h Side.cpp \
        SideFuturelabEast.h \
        SideFuturelabNorth.h \
        SideFuturelabSouth.h \
        SideMainBuildingEast.h \
        SideMainBuildingNorth.h \
        SideMainBuildingSouth.h \
        SideMainBuildingSouthStreetLevel.h \
        SideMainBuildingWest.h

# include paths
AM_CPPFLAGS =  $(CXXFLAGS) $(SDL_CFLAGS) $(EXTERNALS_CFLAGS)


# libs to link
AM_LDFLAGS = $(SDL_LIBS) $(SDL_GFX_LIBS) $(SDL_NET_LIBS) $(SDL_image_LIBS) $(EXTERNALS_LIBS)
