cmake_minimum_required (VERSION 2.8.12)
project (syslog-ng)
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set (BISON_FLAGS "-Wno-other")

set (SYSLOG_NG_VERSION_MAJOR 3)
set (SYSLOG_NG_VERSION_MINOR 8)
set (SYSLOG_NG_VERSION_PATCH alpha0)
set (SYSLOG_NG_VERSION "${SYSLOG_NG_VERSION_MAJOR}.${SYSLOG_NG_VERSION_MINOR}.${SYSLOG_NG_VERSION_PATCH}")

set (SYSLOG_NG_PATH_PREFIX "/usr/local")
set (SYSLOG_NG_PATH_SYSCONFDIR "\${prefix}/etc")
set (SYSLOG_NG_PATH_DATADIR "\${prefix}/etc")
set (SYSLOG_NG_PATH_PIDFILEDIR "\${localstatedir}")
set (SYSLOG_NG_PATH_LOCALSTATEDIR "\${prefix}/var")
set (SYSLOG_NG_MODULE_PATH "\${exec_prefix}/lib/syslog-ng")

include (CheckTypeSize)

set (CMAKE_EXTRA_INCLUDE_FILES sys/socket.h)
check_type_size ("struct sockaddr_storage" STRUCT_SOCKADDR_STORAGE)
set (SYSLOG_NG_HAVE_STRUCT_SOCKADDR_STORAGE ${HAVE_STRUCT_SOCKADDR_STORAGE})
set (CMAKE_EXTRA_INCLUDE_FILES)

include (CheckSymbolExists)

check_symbol_exists (strtoll stdlib.h SYSLOG_NG_HAVE_STRTOLL)
check_symbol_exists (strtoimax inttypes.h SYSLOG_NG_HAVE_STRTOIMAX)
check_symbol_exists (inet_aton sys/socket.h SYSLOG_NG_HAVE_INET_ATON)

find_package(BISON 2.4 REQUIRED)

find_package(Glib 2.10.1 REQUIRED)
include_directories (SYSTEM ${Glib_INCLUDE_DIRS})
pkg_check_modules(IVYKIS REQUIRED ivykis)
include_directories (SYSTEM ${IVYKIS_INCLUDE_DIRS})
pkg_check_modules(EVENTLOG REQUIRED eventlog)
include_directories (SYSTEM ${EVENTLOG_INCLUDE_DIRS})
find_package(FLEX REQUIRED)

function(generate_y_from_ym FileWoExt)
    add_custom_command (OUTPUT ${CMAKE_BINARY_DIR}/${FileWoExt}.y
        COMMAND ${CMAKE_SOURCE_DIR}/lib/merge-grammar.pl ${CMAKE_SOURCE_DIR}/${FileWoExt}.ym > ${CMAKE_BINARY_DIR}/${FileWoExt}.y
        DEPENDS ${CMAKE_SOURCE_DIR}/lib/cfg-grammar.y)
endfunction()

generate_y_from_ym (lib/block-ref-grammar)
flex_target(CfgLexer ${CMAKE_CURRENT_SOURCE_DIR}/lib/cfg-lex.l ${CMAKE_CURRENT_BINARY_DIR}/lib/cfg-lex.c ${CMAKE_CURRENT_BINARY_DIR}/lib/cfg-lex.h)

set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/lib/cfg-lex.h GENERATED)
set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/lib/cfg-lex.c GENERATED)

bison_target(BlockRefGrammar ${CMAKE_BINARY_DIR}/lib/block-ref-grammar.y ${CMAKE_CURRENT_BINARY_DIR}/lib/block-ref-grammar.c COMPILE_FLAGS ${BISON_FLAGS})
add_flex_bison_dependency(CfgLexer BlockRefGrammar)

bison_target(CfgGrammar lib/cfg-grammar.y ${CMAKE_CURRENT_BINARY_DIR}/lib/cfg-grammar.c COMPILE_FLAGS ${BISON_FLAGS})
add_flex_bison_dependency(CfgLexer CfgGrammar)

add_subdirectory(lib)

add_library(syslog-ng ${LIB_SOURCES} ${LIB_HEADERS} ${CMAKE_CURRENT_BINARY_DIR}/lib/cfg-lex.h)
target_link_libraries (syslog-ng ${Glib_LIBRARIES} ${IVYKIS_LIBRARIES} ${EVENTLOG_LIBRARIES} ${FLEX_LIBRARIES} ${BISON_LIBRARIES})

include (CheckIncludeFiles)

include_directories (${CMAKE_CURRENT_BINARY_DIR})
include_directories (${CMAKE_CURRENT_BINARY_DIR}/lib)
include_directories (${CMAKE_SOURCE_DIR}/lib)
include_directories (${CMAKE_SOURCE_DIR})

configure_file (${CMAKE_CURRENT_SOURCE_DIR}/syslog-ng-config.h.in ${CMAKE_CURRENT_BINARY_DIR}/syslog-ng-config.h)

MESSAGE(STATUS "${FLEX_CfgLexer_OUTPUT_HEADERS}")
