# facade

# load externals variables
include $(top_srcdir)/externals/externals.mk

# the library to build
lib_LTLIBRARIES = libfacade.la

# libs sources, headers here because we dont want to install them
libfacade_la_SOURCES = \
        Building.h \
        Facade.cpp \
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

# lib headers to install
include_HEADERS = Facade.h

# include paths
AM_CPPFLAGS =  $(CXXFLAGS) $(SDL_CFLAGS) $(EXTERNALS_CFLAGS)


# libs to link
AM_LDFLAGS = $(SDL_LIBS) $(SDL_GFX_LIBS) $(SDL_NET_LIBS) $(SDL_image_LIBS) $(EXTERNALS_LIBS)
