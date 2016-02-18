cmake_minimum_required (VERSION 2.8.12)
project (syslog-ng)
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/Modules")
set (CMAKE_POSITION_INDEPENDENT_CODE 1)
set (BISON_FLAGS "-Wno-other")

set (SYSLOG_NG_VERSION_MAJOR 3)
set (SYSLOG_NG_VERSION_MINOR 8)
set (SYSLOG_NG_VERSION_PATCH alpha0)
set (SYSLOG_NG_VERSION "${SYSLOG_NG_VERSION_MAJOR}.${SYSLOG_NG_VERSION_MINOR}.${SYSLOG_NG_VERSION_PATCH}")
set (SYSLOG_NG_SOURCE_REVISION ${SYSLOG_NG_VERSION})

set (SYSLOG_NG_PATH_PREFIX "/usr/local")
set (SYSLOG_NG_PATH_SYSCONFDIR "\${prefix}/etc")
set (SYSLOG_NG_PATH_DATADIR "\${prefix}/etc")
set (SYSLOG_NG_PATH_PIDFILEDIR "\${localstatedir}")
set (SYSLOG_NG_PATH_LOCALSTATEDIR "\${prefix}/var")
set (SYSLOG_NG_MODULE_PATH "\${exec_prefix}/lib/syslog-ng")
set (SYSLOG_NG_PATH_EXECPREFIX "\${prefix}")
set (SYSLOG_NG_PATH_LIBEXECDIR "\${exec_prefix}/libexec")
set (SYSLOG_NG_PATH_DATAROOTDIR "\${prefix}/share")

include (CheckTypeSize)

set (CMAKE_EXTRA_INCLUDE_FILES sys/socket.h)
check_type_size ("struct sockaddr_storage" STRUCT_SOCKADDR_STORAGE)
set (SYSLOG_NG_HAVE_STRUCT_SOCKADDR_STORAGE ${HAVE_STRUCT_SOCKADDR_STORAGE})
set (CMAKE_EXTRA_INCLUDE_FILES)

include (CheckSymbolExists)

check_symbol_exists (strtoll stdlib.h SYSLOG_NG_HAVE_STRTOLL)
check_symbol_exists (strtoimax inttypes.h SYSLOG_NG_HAVE_STRTOIMAX)
check_symbol_exists (inet_aton "sys/socket.h;netinet/in.h;arpa/inet.h" SYSLOG_NG_HAVE_INET_ATON)

find_package(BISON 2.4 REQUIRED)
find_package(GLIB 2.10.1 REQUIRED)
find_package(Ivykis REQUIRED)
find_package(Eventlog REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(FLEX REQUIRED)
find_package(Gettext REQUIRED QUIET)

set(CORE_INCLUDE_DIRS
    ${Eventlog_INCLUDE_DIRS}
    ${Ivykis_INCLUDE_DIRS}
    ${GLIB_INCLUDE_DIRS}
    ${OpenSSL_INCLUDE_DIRS}}
    ${GETTEXT_INCLUDE_DIR}
)

set(CORE_LIBRARIES
    ${Eventlog_LIBRARIES}
    ${Ivykis_LIBRARIES}
    ${GLIB_LIBRARIES}
    ${OpenSSL_LIBRARIES}
    ${FLEX_LIBRARIES}
    ${BISON_LIBRARIES}
    ${GETTEXT_LIBRARIES}
)

include_directories(SYSTEM ${CORE_INCLUDE_DIRS})

function(generate_y_from_ym FileWoExt)
    add_custom_command (OUTPUT ${CMAKE_BINARY_DIR}/${FileWoExt}.y
        COMMAND ${CMAKE_SOURCE_DIR}/lib/merge-grammar.pl ${CMAKE_SOURCE_DIR}/${FileWoExt}.ym > ${CMAKE_BINARY_DIR}/${FileWoExt}.y
        DEPENDS ${CMAKE_SOURCE_DIR}/lib/cfg-grammar.y
                ${CMAKE_SOURCE_DIR}/${FileWoExt}.ym)
endfunction()

include_directories (${CMAKE_BINARY_DIR}/lib)
include_directories (${CMAKE_BINARY_DIR})
include_directories (${CMAKE_SOURCE_DIR}/lib)
include_directories (${CMAKE_SOURCE_DIR})
add_subdirectory(lib)
add_subdirectory(modules)

include (CheckIncludeFiles)

configure_file (${CMAKE_CURRENT_SOURCE_DIR}/syslog-ng-config.h.in ${CMAKE_CURRENT_BINARY_DIR}/syslog-ng-config.h)

MESSAGE(STATUS "${FLEX_CfgLexer_OUTPUT_HEADERS}")
