set(AFFILE_HEADERS
    "logproto-linux-proc-kmsg-reader.h"
    "logproto-file-writer.h"
    "poll-file-changes.h"
    "affile-common.h"
    "affile-source.h"
    "affile-dest.h"
    "affile-parser.h"
    "${CMAKE_CURRENT_BINARY_DIR}/affile-grammar.h"
)

set(AFFILE_SOURCES
    "logproto-file-writer.c"
    "poll-file-changes.c"
    "affile-common.c"
    "affile-source.c"
    "affile-dest.c"
    "affile-parser.c"
    "affile-plugin.c"
    "${CMAKE_CURRENT_BINARY_DIR}/affile-grammar.c"
)

generate_y_from_ym(modules/affile/affile-grammar)

bison_target(AffileGrammar
    ${CMAKE_CURRENT_BINARY_DIR}/affile-grammar.y
    ${CMAKE_CURRENT_BINARY_DIR}/affile-grammar.c
    COMPILE_FLAGS ${BISON_FLAGS})

include_directories (${CMAKE_CURRENT_BINARY_DIR})
include_directories (${CMAKE_CURRENT_SOURCE_DIR})
add_library(affile MODULE ${AFFILE_SOURCES})
target_link_libraries(affile PRIVATE syslog-ng)

install(TARGETS affile
    LIBRARY DESTINATION lib/syslog-ng/
    COMPONENT affile)
