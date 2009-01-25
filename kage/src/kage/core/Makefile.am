LIBKAGE_CORE_INCLUDES = $(DEP_LOG4CXX_CFLAGS) $(DEP_OIS_CFLAGS) -I@top_srcdir@/include

LIBKAGE_CORE_LIBADD = $(DEP_LOG4CXX_LIBS) $(DEP_OIS_CFLAGS)

LIBKAGE_CORE_SOURCES = $(top_srcdir)/src/kage/core/sys_application.cc \
                       $(top_srcdir)/src/kage/core/sys_fsm.cc \
                       $(top_srcdir)/src/kage/core/sys_task.cc \
                       $(top_srcdir)/src/kage/core/sys_system.cc \
                       $(top_srcdir)/src/kage/core/utils_logging.cc \
                       $(top_srcdir)/src/kage/core/input_system.cc

INCLUDES = $(LIBKAGE_CORE_INCLUDES)

noinst_LTLIBRARIES = libkage-core.la
libkage_core_la_SOURCES = $(LIBKAGE_CORE_SOURCES)
libkage_core_la_LIBADD = $(LIBKAGE_CORE_LIBADD)


