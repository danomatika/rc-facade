
# load externals variables
include $(top_srcdir)/externals/externals.mk

# programs to build
bin_PROGRAMS = facade-simulator

# bin sources, headers here because we dont want to install them
facade_simulator_SOURCES = \
        Common.h Config.h Config.cpp \
        App.h App.cpp \
        main.cpp

# include paths
facade_simulator_CPPFLAGS = $(CXXFLAGS) $(SDL_CFLAGS) $(EXTERNALS_CFLAGS) \
					-I$(top_srcdir)/src

# local libs to link
facade_simulator_LDADD = -L$(top_builddir)/src/facade -lfacade \
						 -L$(top_builddir)/src/common -lcommon \
						 $(EXTERNALS_LIBS)

# libs to link
facade_simulator_LDFLAGS = $(SDL_LIBS) $(LO_LIBS) $(SDL_gfx_LIBS) $(SDL_NET_LIBS) \
					$(SDL_image_LIBS) $(SDL_TTF_LIBS)

