set(LINUX_KMSG_FORMAT_SOURCES
    linux-kmsg-format.c
    linux-kmsg-format.h
    linux-kmsg-format-plugin.c
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_library(linux-kmsg-format MODULE ${LINUX_KMSG_FORMAT_SOURCES})
add_dependencies(linux-kmsg-format syslog-ng)
