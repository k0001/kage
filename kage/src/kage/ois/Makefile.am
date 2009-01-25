if WITH_OIS

    LIBKAGE_OIS_INCLUDES = $(DEP_LOG4CXX_CFLAGS) $(DEP_OIS_CFLAGS) -I@top_srcdir@/include

    LIBKAGE_OIS_LIBADD = $(DEP_LOG4CXX_LIBS) $(DEP_OIS_CFLAGS)

    LIBKAGE_OIS_SOURCES = $(top_srcdir)/src/kage/ois/input_system.cc

    INCLUDES = $(LIBKAGE_OIS_INCLUDES)

    noinst_LTLIBRARIES = libkage-ois.la
    libkage_ois_la_SOURCES = $(LIBKAGE_OIS_SOURCES)
    libkage_ois_la_LIBADD = $(LIBKAGE_OIS_LIBADD)

endif

