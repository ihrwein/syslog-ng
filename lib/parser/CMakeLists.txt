set(PARSER_HEADERS
    parser/parser-expr.h
    parser/parser-expr-parser.h
    PARENT_SCOPE)

set(PARSER_SOURCES
    parser/parser-expr.c
    parser/parser-expr-parser.c
    PARENT_SCOPE)

#BUILT_SOURCES +=                 \
#    lib/parser/parser-expr-grammar.y    \
#    lib/parser/parser-expr-grammar.c    \
#    lib/parser/parser-expr-grammar.h
#
#EXTRA_DIST += lib/parser/parser-expr-grammar.ym
