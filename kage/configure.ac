AC_INIT(include/kage/core/core.hh)
AM_INIT_AUTOMAKE(kage,0.1)

AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LIBTOOL

PKG_CHECK_MODULES(DEP_LOG4CXX, [liblog4cxx])

dnl Ogre support
AC_MSG_CHECKING([wether to enable Ogre support])
AC_ARG_WITH(ogre,
    [  --with-ogre 		  Ogre support],
    with_ogre=$withval,
    with_ogre=[no])
AC_MSG_RESULT($with_ogre)
if test "x$with_ogre" = "xyes"; then
    PKG_CHECK_MODULES(DEP_OGRE, OGRE >= 1.6)
    AC_DEFINE(WITH_OGRE)
fi
AM_CONDITIONAL(WITH_OGRE, test "x$with_ogre" = "xyes")

dnl OIS support
AC_MSG_CHECKING([wether to enable OIS support])
AC_ARG_WITH(ois,
    [  --with-ois 		  OIS support],
    with_ois=$withval,
    with_ois=[no])
AC_MSG_RESULT($with_ogre)
if test "x$with_ois" = "xyes"; then
    AC_DEFINE(WITH_OIS)
fi
AM_CONDITIONAL(WITH_OIS, test "x$with_ois" = "xyes")

dnl OIS is needed by core anyways.
PKG_CHECK_MODULES(DEP_OIS, OIS >= 1.2)

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

