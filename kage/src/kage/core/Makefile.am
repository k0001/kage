LIBKAGE_RELEASE = 0.1
LIBKAGE_VERSION_INFO = 0:0:0

INCLUDES = $(DEPS_CFLAGS) -I@top_srcdir@/include

lib_LTLIBRARIES = libkage.la
libkage_la_SOURCES = sys_application.cc \
                        sys_fsm.cc \
                        sys_system.cc \
                        sys_task.cc \
                        utils_logging.cc
libkage_la_LDFLAGS = -version-info $(LIBKAGE_VERSION_INFO) -release $(LIBKAGE_RELEASE)
libkage_la_LIBADD = $(DEPS_LIBS)

library_includedir = $(includedir)/kage/kage/core
library_include_HEADERS = @top_srcdir@/include/kage/core/core.hh \
                          @top_srcdir@/include/kage/core/globals.hh \
                          @top_srcdir@/include/kage/core/graphics_system.hh \
                          @top_srcdir@/include/kage/core/input_system.hh \
                          @top_srcdir@/include/kage/core/sys_application.hh \
                          @top_srcdir@/include/kage/core/sys_fsm.hh \
                          @top_srcdir@/include/kage/core/sys_system.hh \
                          @top_srcdir@/include/kage/core/sys_task.hh \
                          @top_srcdir@/include/kage/core/utils_logging.hh


pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = kage-$(LIBKAGE_RELEASE).pc
