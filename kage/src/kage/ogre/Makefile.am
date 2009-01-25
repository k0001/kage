if WITH_OGRE

    LIBKAGE_OGRE_INCLUDES = $(DEP_LOG4CXX_CFLAGS) $(DEP_OGRE_CFLAGS) -I@top_srcdir@/include

    LIBKAGE_OGRE_LIBADD = $(DEP_LOG4CXX_LIBS) $(DEP_OGRE_CFLAGS)

    LIBKAGE_OGRE_SOURCES = $(top_srcdir)/src/kage/ogre/graphics_system.cc

    INCLUDES = $(LIBKAGE_OGRE_INCLUDES)

    noinst_LTLIBRARIES = libkage-ogre.la
    libkage_ogre_la_SOURCES = $(LIBKAGE_OGRE_SOURCES)
    libkage_ogre_la_LIBADD = $(LIBKAGE_OGRE_LIBADD)

endif

