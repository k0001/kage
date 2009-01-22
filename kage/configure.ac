AC_INIT(include/kage/core/core.hh)
AM_INIT_AUTOMAKE(kage,0.1)

AC_PROG_CC
AC_PROG_CXX

PKG_CHECK_MODULES(DEPS, OIS >= 1.2)
AC_SUBST(DEPS_CFLAGS)
AC_SUBST(DEPS_LIBS)

AC_PROG_INSTALL
AC_PROG_LIBTOOL

AC_OUTPUT(Makefile \
          src/Makefile \
          src/kage/Makefile \
          src/kage/core/Makefile \
          src/kage/core/kage-0.1.pc \
          src/kage/ogre/Makefile \
          src/kage/ois/Makefile \
          include/Makefile \
          include/kage/Makefile \
          include/kage/core/Makefile \
          include/kage/ogre/Makefile \
          include/kage/ois/Makefile)

