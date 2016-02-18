
set(AFSMTP_SOURCES
    afsmtp.c
    afsmtp.h
    afsmtp-parser.c
    afsmtp-parser.h
    ${CMAKE_CURRENT_BINARY_DIR}/afsmtp-grammar.h
    ${CMAKE_CURRENT_BINARY_DIR}/afsmtp-grammar.c
)

generate_y_from_ym(modules/afsmtp/afsmtp-grammar)

bison_target(AfsmtpGrammar
    ${CMAKE_CURRENT_BINARY_DIR}/afsmtp-grammar.y
    ${CMAKE_CURRENT_BINARY_DIR}/afsmtp-grammar.c
    COMPILE_FLAGS ${BISON_FLAGS})
#add_flex_bison_dependency(CfgLexer AffileGrammar)

include_directories (${CMAKE_CURRENT_BINARY_DIR})
include_directories (${CMAKE_CURRENT_SOURCE_DIR})
add_library(afsmtp MODULE ${AFSMTP_SOURCES})

add_dependencies(afsmtp syslog-ng)
