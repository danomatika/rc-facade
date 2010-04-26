# external libs variables

# directories to build (rel to top dir)
EXTERNALS_DIRS = oscframework xmlframework visualframework tclap

# includes
EXTERNALS_CFLAGS = \
    -I$(top_srcdir)/externals/oscframework/src \
    -I$(top_srcdir)/externals/xmlframework/src \
    -I$(top_srcdir)/externals/visualframework/src \
    -I$(top_srcdir)/externals/visualframework/src/visualframework \
    -I$(top_srcdir)/externals

# libs to link
EXTERNALS_LIBS = \
    -L$(top_builddir)/externals/visualframework/externals/lib \
    -L$(top_builddir)/externals/oscframework/src/oscframework \
    -L$(top_builddir)/externals/xmlframework/src/xmlframework \
    -L$(top_builddir)/externals/visualframework/src/visualframework \
    -loscframework -lxmlframework -lvisualframework
