set(REWRITE_HEADERS
	rewrite-expr.h
	rewrite-set-tag.h
	rewrite-set.h
	rewrite-subst.h
	rewrite-expr-parser.h
	rewrite-groupset.h)

set(REWRITE_SOURCES
	rewrite-expr.c
	rewrite-set-tag.c
	rewrite-set.c
	rewrite-subst.c
	rewrite-expr-parser.c
	rewrite-groupset.c)

#BUILT_SOURCES += 				\
#	lib/rewrite/rewrite-expr-grammar.y	\
#	lib/rewrite/rewrite-expr-grammar.c	\
#	lib/rewrite/rewrite-expr-grammar.h
#
#EXTRA_DIST += lib/rewrite/rewrite-expr-grammar.ym
