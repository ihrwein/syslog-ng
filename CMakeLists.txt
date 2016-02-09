cmake_minimum_required (VERSION 2.8.12)
project (syslog-ng)

set (SYSLOG_NG_VERSION_MAJOR 3)
set (SYSLOG_NG_VERSION_MINOR 8)
set (SYSLOG_NG_VERSION_PATH alpha0)

find_package(BISON 2.4 REQUIRED)

add_subdirectory(lib)
