LIBKAGE_OIS_RELEASE = 0.1
LIBKAGE_OIS_VERSION_INFO = 0:0:0

INCLUDES = $(DEP_OIS_CFLAGS) -I@top_srcdir@/include

lib_LTLIBRARIES = libkage-ois.la
libkage_ois_la_SOURCES = input_system.cc
libkage_ois_la_LDFLAGS = -version-info $(LIBKAGE_OIS_VERSION_INFO) -release $(LIBKAGE_OIS_RELEASE)
libkage_ois_la_LIBADD = $(DEP_OIS_LIBS)

library_includedir = $(includedir)/kage/ois
library_include_HEADERS = @top_srcdir@/include/kage/ois/ois.hh \
                          @top_srcdir@/include/kage/ois/input_system.hh

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = kage-ois.pc
