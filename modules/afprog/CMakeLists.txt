
set(AFPROG_SOURCES
    afprog.c
    afprog.h
    afprog-parser.c
    afprog-parser.h
    afprog-plugin.c
    ${CMAKE_CURRENT_BINARY_DIR}/afprog-grammar.h
    ${CMAKE_CURRENT_BINARY_DIR}/afprog-grammar.c
)

generate_y_from_ym(modules/afprog/afprog-grammar)

bison_target(AfprogGrammar
    ${CMAKE_CURRENT_BINARY_DIR}/afprog-grammar.y
    ${CMAKE_CURRENT_BINARY_DIR}/afprog-grammar.c
    COMPILE_FLAGS ${BISON_FLAGS})
#add_flex_bison_dependency(CfgLexer AffileGrammar)

include_directories (${CMAKE_CURRENT_BINARY_DIR})
include_directories (${CMAKE_CURRENT_SOURCE_DIR})
add_library(afprog MODULE ${AFPROG_SOURCES})

add_dependencies(afprog syslog-ng)
