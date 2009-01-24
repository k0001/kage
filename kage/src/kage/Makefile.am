LIBKAGE_RELEASE = 0.1
LIBKAGE_VERSION_INFO = 0:0:0

LIBKAGE_INCLUDES = $(DEP_LOG4CXX_CFLAGS) \
                   $(DEP_OIS_CFLAGS) \
                  -I@top_srcdir@/include

LIBKAGE_LIBADD = $(DEP_LOG4CXX_LIBS) \
                 $(DEP_OIS_CFLAGS)

LIBKAGE_SOURCES = $(top_srcdir)/src/kage/core/sys_application.cc \
                  $(top_srcdir)/src/kage/core/sys_fsm.cc \
                  $(top_srcdir)/src/kage/core/sys_task.cc \
                  $(top_srcdir)/src/kage/core/sys_system.cc \
                  $(top_srcdir)/src/kage/core/utils_logging.cc


if WITH_OGRE
    LIBKAGE_INCLUDES += $(DEP_OGRE_CFLAGS)
    LIBKAGE_LIBADD += $(DEP_OGRE_LIBS)
    LIBKAGE_SOURCES += $(top_srcdir)/src/kage/ogre/graphics_system.cc
endif

if WITH_OIS
    LIBKAGE_SOURCES += $(top_srcdir)/src/kage/ois/input_system.cc
endif

INCLUDES = $(LIBKAGE_INCLUDES)

lib_LTLIBRARIES = libkage.la
libkage_la_SOURCES = $(LIBKAGE_SOURCES)
libkage_la_LDFLAGS = -version-info $(LIBKAGE_VERSION_INFO) -release $(LIBKAGE_RELEASE)
libkage_la_LIBADD = $(LIBKAGE_LIBADD)

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = $(top_srcdir)/src/kage/kage.pc
