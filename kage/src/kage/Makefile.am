SUBDIRS = core ogre ois

LIBKAGE_RELEASE = 0.1
LIBKAGE_VERSION_INFO = 0:0:0

LIBKAGE_LIBADD = $(top_srcdir)/src/kage/core/libkage-core.la

if WITH_OIS
    LIBKAGE_LIBADD += $(top_srcdir)/src/kage/ois/libkage-ois.la
endif

if WITH_OGRE
    LIBKAGE_LIBADD += $(top_srcdir)/src/kage/ogre/libkage-ogre.la
endif

lib_LTLIBRARIES = libkage.la
libkage_la_SOURCES =
libkage_la_LIBADD = $(LIBKAGE_LIBADD)
libkage_la_LDFLAGS = -version-info $(LIBKAGE_VERSION_INFO) -release $(LIBKAGE_RELEASE)

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = $(top_srcdir)/src/kage/kage.pc

