LIBKAGE_OGRE_RELEASE = 0.1
LIBKAGE_OGRE_VERSION_INFO = 0:0:0

INCLUDES = $(DEP_OGRE_CFLAGS) -I@top_srcdir@/include

lib_LTLIBRARIES = libkage-ogre.la
libkage_ogre_la_SOURCES = graphics_system.cc
libkage_ogre_la_LDFLAGS = -version-info $(LIBKAGE_OGRE_VERSION_INFO) -release $(LIBKAGE_OGRE_RELEASE)
libkage_ogre_la_LIBADD = $(DEP_OGRE_LIBS)

library_includedir = $(includedir)/kage/ogre
library_include_HEADERS = @top_srcdir@/include/kage/ogre/graphics_system.hh

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = kage-ogre.pc
