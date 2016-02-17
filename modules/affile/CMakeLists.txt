set(AFFILE_SOURCES
    logproto-linux-proc-kmsg-reader.h
    logproto-file-writer.c
    logproto-file-writer.h
    poll-file-changes.c
    poll-file-changes.h
    affile-common.c
    affile-common.h
    affile-source.c
    affile-source.h
    affile-dest.c
    affile-dest.h
    affile-parser.c
    affile-parser.h
    affile-plugin.c
    ${CMAKE_CURRENT_BINARY_DIR}/affile-grammar.h
    ${CMAKE_CURRENT_BINARY_DIR}/affile-grammar.c
)

generate_y_from_ym(modules/affile/affile-grammar)

bison_target(AffileGrammar
    ${CMAKE_CURRENT_BINARY_DIR}/affile-grammar.y
    ${CMAKE_CURRENT_BINARY_DIR}/affile-grammar.c
    COMPILE_FLAGS ${BISON_FLAGS})
#add_flex_bison_dependency(CfgLexer AffileGrammar)

include_directories (${CMAKE_CURRENT_BINARY_DIR})
include_directories (${CMAKE_CURRENT_SOURCE_DIR})
add_library(affile MODULE ${AFFILE_SOURCES})

add_dependencies(affile syslog-ng)
