m4_define([package_version], [0.1])

AC_INIT([libcga], [package_version], [mfulz@olznet.de], [libcga])
AM_INIT_AUTOMAKE([foreign subdir-objects])
AC_CONFIG_MACRO_DIR([m4])
LT_INIT([])
AC_CANONICAL_HOST

AC_CONFIG_MACRO_DIRS([m4])

dnl Set versions
AC_SUBST([PACKAGE_VERSION], [package_version])

dnl libcga ABI version (current:revision:age)
AC_SUBST(TCTOR_ABI_VERSION, [0:0:0])

dnl Enable doxygen documentation
AC_ARG_ENABLE([doxygen],
    AS_HELP_STRING([--enable-doxygen], [Enable Doxygen documentation]))

dnl -- setting pathes --
if test "x$prefix" = "xNONE"; then
    prefix=/usr/local
fi
PREFIX=$prefix
AC_SUBST([PREFIX_PATH], ["#define PREFIX_PATH \"${PREFIX}\""])
dnl --------------------

dnl -- setting version --
AC_SUBST([VERSION], ["#define VERSION \"$PACKAGE_VERSION\""])
AC_SUBST([ABI_VERSION], ["#define ABI_VERSION \"$TCTOR_ABI_VERSION\""])
dnl ---------------------

AC_PROG_CC

AS_IF([test "x$enable_doxygen" = "xyes"], [
       AC_CHECK_PROGS([DOXYGEN], [doxygen])
       if test -z "$DOXYGEN"; then
           AC_MSG_ERROR(Doxygen not found)
       fi])
AM_CONDITIONAL([HAS_DOXYGEN], [test "x$enable_doxygen" = "xyes"])
AM_COND_IF([HAS_DOXYGEN], [AC_CONFIG_FILES([docs/Doxyfile])])


AC_CONFIG_FILES([cga-$PACKAGE_VERSION.pc:pkgconfig/cga.pc.in])

AC_CONFIG_FILES([libcga/include/cga.h])
AC_OUTPUT([Makefile])
