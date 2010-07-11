# external libs variables

# directories to build (rel to top dir)
EXTERNALS_DIRS = oscframework xmlframework visualframework tclap

# includes
EXTERNALS_CFLAGS = \
    -I$(top_srcdir)/src/externals/oscframework \
    -I$(top_srcdir)/src/externals/xmlframework \
    -I$(top_srcdir)/src/externals/visualframework \
    -I$(top_srcdir)/src/externals

# libs to link
EXTERNALS_LIBS = \
    -L$(top_builddir)/src/externals/oscframework/ \
    -L$(top_builddir)/src/externals/xmlframework/ \
    -L$(top_builddir)/src/externals/visualframework/ \
    -loscframework -lxmlframework -lvisualframework
