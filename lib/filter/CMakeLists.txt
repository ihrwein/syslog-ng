set(FILTER_HEADERS
    filter/filter-expr.h
    filter/filter-op.h
    filter/filter-cmp.h
    filter/filter-in-list.h
    filter/filter-tags.h
    filter/filter-netmask.h
    filter/filter-netmask6.h
    filter/filter-call.h
    filter/filter-re.h
    filter/filter-pri.h
    filter/filter-pipe.h
    filter/filter-expr-parser.h
    ${CMAKE_CURRENT_BINARY_DIR}/filter-expr-grammar.h
    PARENT_SCOPE)

set(FILTER_SOURCES
    filter/filter-expr.c
    filter/filter-op.c
    filter/filter-cmp.c
    filter/filter-in-list.c
    filter/filter-tags.c
    filter/filter-netmask.c
    filter/filter-netmask6.c
    filter/filter-call.c
    filter/filter-re.c
    filter/filter-pri.c
    filter/filter-pipe.c
    filter/filter-expr-parser.c
    ${CMAKE_CURRENT_BINARY_DIR}/filter-expr-grammar.c
    PARENT_SCOPE)

generate_y_from_ym (lib/filter/filter-expr-grammar)

bison_target(FilterExprGrammar
    ${CMAKE_CURRENT_BINARY_DIR}/filter-expr-grammar.y
    ${CMAKE_CURRENT_BINARY_DIR}/filter-expr-grammar.c
    COMPILE_FLAGS ${BISON_FLAGS})

add_flex_bison_dependency(CfgLexer FilterExprGrammar)

set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/filter-expr-grammar.c GENERATED)
set_source_files_properties(${CMAKE_CURRENT_BINARY_DIR}/filter-expr-grammar.h GENERATED)

#BUILT_SOURCES +=                 \
#    lib/filter/filter-expr-grammar.y    \
#    lib/filter/filter-expr-grammar.c    \
#    lib/filter/filter-expr-grammar.h
#
#EXTRA_DIST += lib/filter/filter-expr-grammar.ym
#
#include lib/filter/tests/Makefile.am
