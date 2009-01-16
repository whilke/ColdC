# ########## Project setup ##########
PROJECT(src)
CMAKE_MINIMUM_REQUIRED(VERSION 2.4.5)

# ######### General setup ##########
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/modules)
INCLUDE_DIRECTORIES(/usr/local/include)

INCLUDE(${CMAKE_ROOT}/Modules/CheckIncludeFile.cmake)
CHECK_INCLUDE_FILE(vfork.h HAVE_VFORK_H)
CHECK_INCLUDE_FILE(gdbm.h DBM_H_FILE)
CHECK_INCLUDE_FILE(unistd.h HAVE_UNISTD_H)

INCLUDE(${CMAKE_ROOT}/Modules/CheckTypeSize.cmake)
CHECK_TYPE_SIZE("char" SIZEOF_CHAR)
CHECK_TYPE_SIZE("short" SIZEOF_SHORT)
CHECK_TYPE_SIZE("int" SIZEOF_INT)
CHECK_TYPE_SIZE("long" SIZEOF_LONG)
CHECK_TYPE_SIZE("long long" SIZEOF_LLONG)
CHECK_TYPE_SIZE("float" SIZEOF_FLOAT)
CHECK_TYPE_SIZE("double" SIZEOF_DOUBLE)
CHECK_TYPE_SIZE("long double" SIZEOF_LDOUBLE)

INCLUDE(${CMAKE_ROOT}/Modules/CheckFunctionExists.cmake)
CHECK_FUNCTION_EXISTS(strerror HAVE_STRERROR)
CHECK_FUNCTION_EXISTS(strstr HAVE_STRSTR)
CHECK_FUNCTION_EXISTS(strftime HAVE_STRFTIME)
CHECK_FUNCTION_EXISTS(getrusage HAVE_GETRUSAGE)
CHECK_FUNCTION_EXISTS(gettimeofday HAVE_GETTIMEOFDAY)
CHECK_FUNCTION_EXISTS(memmove HAVE_MEMMOVE)
CHECK_FUNCTION_EXISTS(mkdir HAVE_MKDIR)
CHECK_FUNCTION_EXISTS(select HAVE_SELECT)
CHECK_FUNCTION_EXISTS(socket HAVE_SOCKET)
CHECK_FUNCTION_EXISTS(vprintf HAVE_VPRINTF)
CHECK_FUNCTION_EXISTS(inet_aton HAVE_INET_ATON)
CHECK_FUNCTION_EXISTS(rint HAVE_RINT)
CHECK_FUNCTION_EXISTS(strchr HAVE_STRCHR)
CHECK_FUNCTION_EXISTS(strcspn HAVE_STRCSPN)


CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/include/config.h.in 
			${CMAKE_SOURCE_DIR}/include/config.h)


find_program(LEX_EXE
	flex
)
if(LEX_EXE STREQUAL "LEX_EXE-NOTFOUND")
	message(FATAL_ERROR "dear user, plase install flex!")
endif(LEX_EXE STREQUAL "LEX_EXE-NOTFOUND")

find_program(YACC_EXE
	yacc
)
if(YACC_EXE STREQUAL "YACC_EXE-NOTFOUND")
	message(FATAL_ERROR "dear user, plase install bison!")
endif(YACC_EXE STREQUAL "YACC_EXE-NOTFOUND")

# reuseable cmake macro for yacc
MACRO(YACC_FILE _filename)
	GET_FILENAME_COMPONENT(_basename ${_filename} NAME_WE)
	ADD_CUSTOM_COMMAND(
		OUTPUT  ${CMAKE_CURRENT_SOURCE_DIR}/${_basename}.c
				${CMAKE_CURRENT_BUILD_DIR}/${_basename}.h
		COMMAND ${YACC_EXE} -d
				-o ${CMAKE_CURRENT_SOURCE_DIR}/${_basename}.c
				${CMAKE_CURRENT_SOURCE_DIR}/${_filename}
		DEPENDS ${_filename}
	)
ENDMACRO(YACC_FILE)

YACC_FILE(grammar.y)

# ########## src executable ##########
# Sources:


SET(src_GRAMMAR
	# GRAMMAR
	grammar.c
)

SET(src_DB
	# DB
	dbpack.c
	binarydb.c
	cache.c
	decode.c
	lookup.c
)

SET(src_IO
	# IO
	io.c
	log.c
	net.c
	file.c
)

SET(src_MISC
	# MISC
	sig.c
	strutil.c
	memory.c
	util.c
	regexp.c
	defs.c
	dns.c
)

SET(src_CRYPT
	# CRYPT
	shs.c
	crypt.c
)


SET(src_DATA
	# DATA
	data/data.c
	data/buffer.c
	data/dict.c
	data/handled_frob.c
	data/ident.c
	data/list.c
	data/object.c
	data/quickhash.c
	data/string.c
)

SET(src_OPS
	# OPS
	ops/buffer.c
	ops/data.c
	ops/dict.c
	ops/error.c
	ops/file.c
	ops/list.c
	ops/math.c
	ops/misc.c
	ops/network.c
	ops/object.c
	ops/operators.c
	ops/string.c
	ops/sys.c
	ops/task.c
)

SET(src_MODULES
	# MODULES
	modules/cdc.c
	modules/cdc_buffer.c
	modules/cdc_dict.c
	modules/cdc_integer.c
	modules/cdc_list.c
	modules/cdc_misc.c
	modules/cdc_string.c
	modules/ext_math.c
)

SET(src_PCODE
	# PCODE
	codegen.c
	execute.c
	opcodes.c
	token.c
	native.c
	#{src_MODULES}
)

SET(src_COMMON
	${src_MODULES}
	${src_DATA}
	${src_DB}
	${src_IO}
	${src_MISC}
	${src_PCODE}
	${src_OPS}
	${src_CRYPT}
	#control.c
)


SET(src_COMPILER
	coldcc.c
	textdb.c
	${src_GRAMMAR}
	${src_COMMON}
)

SET(src_GENESIS
	${src_GRAMMAR}
	${src_COMMON}
	genesis.c
)

# Headers:
SET(src_executable_HDRS
)

# actual target:
ADD_EXECUTABLE(genesis ${src_GENESIS})
ADD_EXECUTABLE(coldcc ${src_COMPILER})

 add_library(dbm42 STATIC IMPORTED)
 add_library(math STATIC IMPORTED)
 set_property(TARGET math PROPERTY IMPORTED_LOCATION /usr/lib/libm.so)
 set_property(TARGET dbm42 PROPERTY IMPORTED_LOCATION /usr/local/lib/db42/libdb.so)
 target_link_libraries(coldcc math dbm42)
 target_link_libraries(genesis math dbm42)
# add install target:
#INSTALL(TARGETS genesis DESTINATION bin)
#INSTALL(TARGETS coldcc DESTINATION bin)
