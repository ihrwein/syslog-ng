set(PARSER_HEADERS
    lib/parser/parser-expr.h
    lib/parser/parser-expr-parser.h
    PARENT_SCOPE)

set(PARSER_SOURCES
    lib/parser/parser-expr.c
    lib/parser/parser-expr-parser.c
    PARENT_SCOPE)

bison_target(parser-expr-grammar parser-expr-grammar.y parser-expr-grammar.c)

#BUILT_SOURCES +=                 \
#    lib/parser/parser-expr-grammar.y    \
#    lib/parser/parser-expr-grammar.c    \
#    lib/parser/parser-expr-grammar.h
#
#EXTRA_DIST += lib/parser/parser-expr-grammar.ym
