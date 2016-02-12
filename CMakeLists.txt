cmake_minimum_required (VERSION 2.8.12)
project (syslog-ng)
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set (SYSLOG_NG_VERSION_MAJOR 3)
set (SYSLOG_NG_VERSION_MINOR 8)
set (SYSLOG_NG_VERSION_PATH alpha0)

set (SYSLOG_NG_PATH_PREFIX "/usr/local")
set (SYSLOG_NG_PATH_SYSCONFDIR "\${prefix}/etc")
set (SYSLOG_NG_PATH_DATADIR "\${prefix}/etc")

find_package(BISON 2.4 REQUIRED)

find_package(Glib 2.10.1 REQUIRED)
include_directories (SYSTEM ${Glib_INCLUDE_DIRS})
pkg_check_modules(IVYKIS REQUIRED ivykis)
include_directories (SYSTEM ${IVYKIS_INCLUDE_DIRS})
pkg_check_modules(EVENTLOG REQUIRED eventlog)
include_directories (SYSTEM ${EVENTLOG_INCLUDE_DIRS})
find_package(FLEX REQUIRED)

flex_target(CfgLexer lib/cfg-lex.l ${CMAKE_CURRENT_BINARY_DIR}/lib/cfg-lex.c COMPILE_FLAGS --header-file=${CMAKE_CURRENT_BINARY_DIR}/lib/cfg-lex.h)
set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/lib/cfg-lex.h GENERATED)

bison_target(BlockRefGrammar lib/block-ref-grammar.ym ${CMAKE_CURRENT_BINARY_DIR}/lib/block-ref-grammar.c)
add_flex_bison_dependency(CfgLexer BlockRefGrammar)

bison_target(CfgGrammar lib/cfg-grammar.y ${CMAKE_CURRENT_BINARY_DIR}/lib/cfg-grammar.c)
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
