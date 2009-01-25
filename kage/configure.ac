AC_INIT(include/kage/core/core.hh)
AM_INIT_AUTOMAKE(kage,0.1)

AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LIBTOOL

AC_SUBST(DEP_LOG4CXX_REQUIRE, "liblog4cxx >= 0.9")
PKG_CHECK_MODULES(DEP_LOG4CXX, ${DEP_LOG4CXX_REQUIRE})

dnl Ogre support
AC_MSG_CHECKING([wether to enable Ogre support])
AC_ARG_WITH(ogre,
    AC_HELP_STRING([--with-ogre], [Add OGRE 3D support]),
    with_ogre=$withval,
    with_ogre=[no])
AC_MSG_RESULT($with_ogre)
if test "x$with_ogre" = "xyes"; then
    AC_SUBST(DEP_OGRE_REQUIRE, "OGRE >= 1.6")
    PKG_CHECK_MODULES(DEP_OGRE, ${DEP_OGRE_REQUIRE})
    AC_DEFINE(WITH_OGRE)
fi
AM_CONDITIONAL(WITH_OGRE, test "x$with_ogre" = "xyes")

dnl OIS support
AC_MSG_CHECKING([wether to enable OIS support])
AC_ARG_WITH(ois,
    AC_HELP_STRING([--with-ois], [Add OIS support]),
    with_ois=$withval,
    with_ois=[yes])
AC_MSG_RESULT($with_ois)
if test "x$with_ois" = "xyes"; then
    AC_DEFINE(WITH_OIS)
fi
AM_CONDITIONAL(WITH_OIS, test "x$with_ois" = "xyes")

dnl OIS is needed by core anyways.
AC_SUBST(DEP_OIS_REQUIRE, "OIS >= 1.2")
PKG_CHECK_MODULES(DEP_OIS, ${DEP_OIS_REQUIRE})

AC_SUBST(DEPS_REQUIRE, "${DEP_LOG4CXX_REQUIRE} ${DEP_OGRE_REQUIRE} ${DEP_OIS_REQUIRE}")
AC_SUBST(DEPS_CFLAGS, "${DEP_LOG4CXX_CFLAGS} ${DEP_OGRE_CFLAGS} ${DEP_OIS_CFLAGS}")
AC_SUBST(DEPS_LIBS, "${DEP_LOG4CXX_LIBS} ${DEP_OGRE_LIBS} ${DEP_OIS_LIBS}")

AC_OUTPUT(Makefile \
          src/Makefile \
          src/kage/Makefile \
          src/kage/kage.pc \
          src/kage/core/Makefile \
          src/kage/ogre/Makefile \
          src/kage/ois/Makefile \
          include/Makefile \
          include/kage/Makefile \
          include/kage/core/Makefile \
          include/kage/ogre/Makefile \
          include/kage/ois/Makefile)

