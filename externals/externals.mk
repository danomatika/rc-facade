# external libs variables

# directories to build (rel to top dir)
EXTERNALS_DIRS = visualframework

# includes
EXTERNALS_CFLAGS = \
    -I$(top_srcdir)/externals/visualframework/externals/include \
    -I$(top_srcdir)/externals/visualframework/src/visualframework

# libs to link
EXTERNALS_LIBS = \
    -L$(top_srcdir)/externals/visualframework/externals/lib \
    -loscpack -ltinyxml \
    -L$(top_srcdir)/externals/visualframework/src/visualframework \
    -lvisualframework
