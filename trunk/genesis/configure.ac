#											   -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.61)
AC_INIT(genesis, 1.1.13.1, dwood@vaul-tec.net)
AC_CONFIG_SRCDIR([src/crypt.c])
AC_CONFIG_HEADER([src/include/config.h])
AC_CONFIG_AUX_DIR(./etc)

# Checks for programs.
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_RANLIB
AC_PROG_YACC

# Checks for libraries.
AC_CHECK_LIB(m, pow)
AC_CHECK_LIB(c, waitpid)
# Ugly-ass DBM detection stuffle snagged from someplace in Google -DGW
AC_CHECK_LIB(gdbm, gdbm_open,[AC_DEFINE(GDBM,[],[GDBM]) DBM_TYPE=gdbm; DBM_LIB=-lgdbm],
  [AC_CHECK_LIB(db, dbm_open,[AC_DEFINE(NDBM,[],[NDBM]) DBM_TYPE=ndbm; DBM_LIB=-ldb],
  [AC_CHECK_LIB(c, dbm_open,[AC_DEFINE(NDBM,[],[NDBM]) DBM_TYPE=ndbm; DBM_LIB=],
  [AC_CHECK_LIB(dbm, dbm_open,[AC_DEFINE(NDBM,[],[NDBM]) DBM_TYPE=ndbm; DBM_LIB=-ldbm],
	 [DBM_TYPE=""])])])])
  AC_MSG_CHECKING([preferred dbm library])
  if test "a$DBM_TYPE" = a; then
	AC_MSG_RESULT(none found)
	AC_MSG_WARN(No dbm library found - using built-in flatfile support)
  else
	AC_MSG_RESULT($DBM_TYPE chosen)
  fi
  AC_SUBST(DBM_LIB)
  AC_SUBST(DBM_TYPE)

# Checks for header files.
AC_HEADER_DIRENT
AC_HEADER_STDC
AC_HEADER_SYS_WAIT
AC_CHECK_HEADERS([dirent.h stdio.h arpa/inet.h fcntl.h limits.h netdb.h netinet/in.h stdlib.h string.h sys/file.h sys/param.h sys/socket.h sys/time.h unistd.h gdbm.h])

# Forcing ndbm.h into the headers, is substituted into include/config.h - DGW
# TODO - Make a better scan :)
AC_CHECK_HEADERS([gdbm-ndbm.h], AC_DEFINE( DBM_H_FILE, [<gdbm-ndbm.h>], [DBM H FILE]))

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_TYPE_UID_T
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_HEADER_TIME
AC_STRUCT_TM
AC_STRUCT_TIMEZONE
AC_CHECK_MEMBER(struct dirent.d_namlen)
AC_CHECK_MEMBER(struct tm.tm_gmtoff)

# Added to stop yacc from puking - DGW
AC_CHECK_SIZEOF(char)
AC_CHECK_SIZEOF(short)
AC_CHECK_SIZEOF(int)
AC_CHECK_SIZEOF(long)
AC_CHECK_SIZEOF(long long)
AC_CHECK_SIZEOF(float)
AC_CHECK_SIZEOF(double)
AC_CHECK_SIZEOF(long double)

# Checks for library functions.
AC_FUNC_CLOSEDIR_VOID
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_FUNC_SELECT_ARGTYPES
AC_TYPE_SIGNAL
AC_FUNC_STAT
AC_FUNC_STRFTIME
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([strchr atexit dup2 floor gethostbyaddr gethostbyname gethostname gettimeofday inet_ntoa memchr memset mkdir pow rint rmdir select socket sqrt strchr finite strcspn strerror strspn vfork strstr strtol strtoul inet_aton memmove getrusage crypt])

# Possibly vestigal endianness check - DGW
AC_C_BIGENDIAN( AC_DEFINE(BYTEORDER, [4321], [Big Endian]),
				AC_DEFINE(BYTEORDER, [1234], [Little Endian]), AC_DEFINE(BYTEORDER, [4321], [UNKNOWN-ASSUME BIG ENDIAN]))

# Everything should look fine(ish), let's get to the fun bits:
# First up, Version Mangling! - DGW

AC_DEFINE_UNQUOTED(VERSION_MAJOR, `echo $PACKAGE_VERSION | cut -d. -f1`, [VERSION MAJOR])
AC_DEFINE_UNQUOTED(VERSION_MINOR, `echo $PACKAGE_VERSION | cut -d. -f2`, [VERSION MINOR])
AC_DEFINE_UNQUOTED(VERSION_PATCH, `echo $PACKAGE_VERSION | cut -d. -f3`, [VERSION PATCH])
AC_DEFINE_UNQUOTED(VERSION_RELEASE, `echo $PACKAGE_VERSION | cut -d. -f4`, [VERSION RELEASE])
AC_SUBST(VERSION, $PACKAGE_VERSION, [VERSION])
AC_SUBST(VMAJOR, `echo $PACKAGE_VERSION | cut -d. -f1`, [VMAJOR])
AC_SUBST(VMINOR, `echo $PACKAGE_VERSION | cut -d. -f2`, [VMINOR])
AC_SUBST(VPATCH, `echo $PACKAGE_VERSION | cut -d. -f3`, [VPATCH])
AC_SUBST(VRELEASE, `echo $PACKAGE_VERSION | cut -d. -f4`, [VRELEASE])

# Now footle with the host stuffle

AC_CANONICAL_BUILD

AC_DEFINE_UNQUOTED(CPU, $build_cpu, [CPU])
AC_DEFINE_UNQUOTED(VENDOR, $build_vendor, [VENDOR])
AC_DEFINE_UNQUOTED(SYS, $build_os, [SYS])
AC_DEFINE_UNQUOTED(SYSTEM_TYPE, $build, [SYSTEM TYPE])
AC_SUBST(CPU, "$build_cpu", [CPU])
AC_SUBST(VENDOR, "$build_vendor", [VENDOR])
AC_SUBST(SYS, "$build_os", [SYS])
AC_SUBST(SYSTEM_TYPE, $build_os, [SYSTEM TYPE])

# Now do the modules!

# Arrange the basic NEED TO KNOW stuff

moddir="src/modules"
modfile="src/modules/moddef.h"
inc="module.inc"
defs="module.defs"
conf="$moddir/mod.conf"

# Get all the relevant stuff.
modules=`grep -v '^ *#' $conf | cut -d'	' -f1`
moddef=`grep -v '^ *#' $conf | cut -d'	' -f1,2`
modname=`grep -v '^ *#' $conf | cut -d'	' -f1,3`

for i in $modules; do
	tmp=`grep "^$i	" $conf | cut -d'	' -f2`
	eval "ac_cv_mod_${i}=$tmp"
	tmp=`grep "^$i	" $conf | cut -d'	' -f3`
	eval "mod_${i}_name=$tmp"
done

objs=""
for i in $modules; do
	if test -r "src/modules/$i.mod"; then
		objs="$objs `grep '^objs ' src/modules/$i.mod|sed -e 's/^objs //'`"
	fi
done

MOD_O=""
for i in $objs; do
	MOD_O="$MOD_O modules/$i"
done

	## now setup the modules
	mod_config=""
	for ac_mod in $modules; do
		if eval "test \"`echo '$ac_cv_mod_'$ac_mod`\" = yes"; then
			mod_config="$mod_config $ac_mod"
		fi
	done

#	if test "$mod_config" != "$modules" -o ! -f $modfile; then
		## odd quoting makes even spacing
		echo "- Generating module files for:" $mod_config
		owd=`pwd`
		cd $moddir
		objs=`perl modbuild $mod_config`;
		cd $owd
		MOD_O=`echo $objs`
AC_SUBST(MOD_O)
AC_PREFIX_DEFAULT(..)

AC_CONFIG_FILES([src/Makefile
				 src/data/Makefile
				 src/modules/Makefile
				 src/ops/Makefile])
AC_OUTPUT
