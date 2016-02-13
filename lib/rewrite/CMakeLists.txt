set(REWRITE_HEADERS
    rewrite/rewrite-expr.h
    rewrite/rewrite-set-tag.h
    rewrite/rewrite-set.h
    rewrite/rewrite-subst.h
    rewrite/rewrite-expr-parser.h
    rewrite/rewrite-groupset.h
    PARENT_SCOPE)

set(REWRITE_SOURCES
    rewrite/rewrite-expr.c
    rewrite/rewrite-set-tag.c
    rewrite/rewrite-set.c
    rewrite/rewrite-subst.c
    rewrite/rewrite-expr-parser.c
    rewrite/rewrite-groupset.c
    PARENT_SCOPE)

generate_y_from_ym (lib/rewrite/rewrite-expr-grammar)

bison_target(RewriteExprGrammar
    ${CMAKE_BINARY_DIR}/lib/rewrite/rewrite-expr-grammar.y
    ${CMAKE_BINARY_DIR}/lib/rewrite/rewrite-expr-grammar.c
    COMPILE_FLAGS ${BISON_FLAGS})

add_flex_bison_dependency(CfgLexer RewriteExprGrammar)
#BUILT_SOURCES +=                 \
#    lib/rewrite/rewrite-expr-grammar.y    \
#    lib/rewrite/rewrite-expr-grammar.c    \
#    lib/rewrite/rewrite-expr-grammar.h
#
#EXTRA_DIST += lib/rewrite/rewrite-expr-grammar.ym
