AC_INIT(include/kage/core/core.hh)
AM_INIT_AUTOMAKE(kage,0.1)

AC_PROG_CC
AC_PROG_CXX

PKG_CHECK_MODULES(DEP_OIS, OIS >= 1.2)
PKG_CHECK_MODULES(DEP_OGRE, OGRE >= 1.6)

AC_PROG_INSTALL
AC_PROG_LIBTOOL

AC_OUTPUT(Makefile \
          src/Makefile \
          src/kage/Makefile \
          src/kage/core/Makefile \
          src/kage/core/kage.pc \
          src/kage/ogre/Makefile \
          src/kage/ogre/kage-ogre.pc \
          src/kage/ois/Makefile \
          src/kage/ois/kage-ois.pc \
          include/Makefile \
          include/kage/Makefile \
          include/kage/core/Makefile \
          include/kage/ogre/Makefile \
          include/kage/ois/Makefile)

