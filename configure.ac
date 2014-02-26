#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.68])
AC_INIT([Neros], [0.1], [i@nyankosama.com])
AM_INIT_AUTOMAKE()
LT_PREREQ([2.4])
LT_INIT([dlopen])

AC_CONFIG_SRCDIR([src/Main.cpp])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CC
AC_PROG_CXX
AC_PROG_INSTALL
#AC_PROG_RANLIB
AM_PROG_CC_C_O
#AM_PROG_AR


# enable or disable features

# Checks for libraries.
#1. checks for pthread

# Checks for header files.
AC_CHECK_HEADERS([stdlib.h pthread.h])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/data/Makefile
                 src/Makefile])

AC_OUTPUT
