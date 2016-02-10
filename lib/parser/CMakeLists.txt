set(PARSER_HEADERS
    parser-expr.h
    parser-expr-parser.h)

set(PARSER_SOURCES
    parser-expr.c
    parser-expr-parser.c)

bison_target(parser-expr-grammar parser-expr-grammar.y parser-expr-grammar.c)

#BUILT_SOURCES +=                 \
#    lib/parser/parser-expr-grammar.y    \
#    lib/parser/parser-expr-grammar.c    \
#    lib/parser/parser-expr-grammar.h
#
#EXTRA_DIST += lib/parser/parser-expr-grammar.ym
