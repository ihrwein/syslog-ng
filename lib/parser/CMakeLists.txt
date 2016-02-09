set(PARSER_HEADERS
    parser-expr.h
    parser-expr-parser.h)

set(PARSER_SOURCES
    parser-expr.c
    parser-expr-parser.c
    parser-expr-grammar.y)

add_library(parser OBJECT ${PARSER_HEADERS} ${PARSER_SOURCES})

#BUILT_SOURCES +=                 \
#    lib/parser/parser-expr-grammar.y    \
#    lib/parser/parser-expr-grammar.c    \
#    lib/parser/parser-expr-grammar.h
#
#EXTRA_DIST += lib/parser/parser-expr-grammar.ym
