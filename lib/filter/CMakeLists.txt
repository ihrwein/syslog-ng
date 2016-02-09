set(FILTER_HEADERS
	filter-expr.h
	filter-op.h
	filter-cmp.h
	filter-in-list.h
	filter-tags.h
	filter-netmask.h
	filter-netmask6.h
	filter-call.h
	filter-re.h
	filter-pri.h
	filter-pipe.h
	filter-expr-parser.h)

set(FILTER_SOURCES
	filter-expr.c
	filter-op.c
	filter-cmp.c
	filter-in-list.c
	filter-tags.c
	filter-netmask.c
	filter-netmask6.c
	filter-call.c
	filter-re.c
	filter-pri.c
	filter-pipe.c
	filter-expr-parser.c)

bison_target(filter-expr-grammar filter-expr-grammar.y filter-expr-grammar.c)

add_library(filter OBJECT ${FILTER_SOURCES} ${FILTER_HEADERS})

#BUILT_SOURCES += 				\
#	lib/filter/filter-expr-grammar.y	\
#	lib/filter/filter-expr-grammar.c	\
#	lib/filter/filter-expr-grammar.h
#
#EXTRA_DIST += lib/filter/filter-expr-grammar.ym
#
#include lib/filter/tests/Makefile.am
