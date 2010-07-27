# external libs variables

# directories to build (rel to top dir)
EXTERNALS_DIRS = oscframework xmlframework visualframework tclap

# includes
EXTERNALS_CFLAGS = \
    -I$(top_srcdir)/externals/oscframework \
    -I$(top_srcdir)/externals/xmlframework \
    -I$(top_srcdir)/externals/visualframework \
    -I$(top_srcdir)/externals

# libs to link
EXTERNALS_LIBS = \
    -L$(top_builddir)/externals/oscframework/ \
    -L$(top_builddir)/externals/xmlframework/ \
    -L$(top_builddir)/externals/visualframework/ \
    -loscframework -lxmlframework -lvisualframework
