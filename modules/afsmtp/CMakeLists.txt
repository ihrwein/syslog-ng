set(AFSMTP_SOURCES
    afsmtp.c
    afsmtp.h
    afsmtp-parser.c
    afsmtp-parser.h
    ${CMAKE_CURRENT_BINARY_DIR}/afsmtp-grammar.h
    ${CMAKE_CURRENT_BINARY_DIR}/afsmtp-grammar.c
)

option(ENABLE_AFSMTP "Enable SMTP destination" ON)

find_package(ESMTP)

if(ESMTP_FOUND AND ENABLE_AFSMTP)
    set(BUILD_AFSMTP ON)
else()
    set(BUILD_AFSMTP OFF)
endif()

if (BUILD_AFSMTP)
    generate_y_from_ym(modules/afsmtp/afsmtp-grammar)

    bison_target(AfsmtpGrammar
        ${CMAKE_CURRENT_BINARY_DIR}/afsmtp-grammar.y
        ${CMAKE_CURRENT_BINARY_DIR}/afsmtp-grammar.c
        COMPILE_FLAGS ${BISON_FLAGS})

    include_directories (${CMAKE_CURRENT_BINARY_DIR})
    include_directories (${CMAKE_CURRENT_SOURCE_DIR})
    include_directories (${ESMTP_INCLUDE_DIR})
    add_library(afsmtp MODULE ${AFSMTP_SOURCES})
    target_link_libraries (afsmtp ${ESMTP_LIBRARIES})

    add_dependencies(afsmtp syslog-ng)
endif()
