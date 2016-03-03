option(ENABLE_PACCT "Enable support for reading Process Accounting files (EXPERIMENTAL, Linux only)." ON)

if (ENABLE_PACCT)
    set(PACCT_FORMAT_SOURCES
        pacct-format.c
        pacct-format.h
        pacct-format-plugin.c
    )

    include_directories(${CMAKE_CURRENT_SOURCE_DIR})
    add_library(pacctformat MODULE ${PACCT_FORMAT_SOURCES})
    add_dependencies(pacctformat syslog-ng)
endif()
