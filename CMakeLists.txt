cmake_minimum_required (VERSION 2.8.12)
project (syslog-ng)
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

set (SYSLOG_NG_VERSION_MAJOR 3)
set (SYSLOG_NG_VERSION_MINOR 8)
set (SYSLOG_NG_VERSION_PATH alpha0)

find_package(BISON 2.4 REQUIRED)

find_package(Glib 2.10.1 REQUIRED)
include_directories (SYSTEM ${Glib_INCLUDE_DIRS})

add_subdirectory(lib)

add_library(syslog-ng ${LIB_SOURCES} ${LIB_HEADERS})
target_link_libraries (syslog-ng ${Glib_LIBRARIES})

include (CheckIncludeFiles)

include_directories (SYSTEM ${CMAKE_CURRENT_BINARY_DIR})
include_directories (SYSTEM "${CMAKE_SOURCE_DIR}/lib")
configure_file (${CMAKE_CURRENT_SOURCE_DIR}/syslog-ng-config.h.in ${CMAKE_CURRENT_BINARY_DIR}/syslog-ng-config.h)
