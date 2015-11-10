#ifndef RUST_FILTER_H_INCLUDED
#define RUST_FILTER_H_INCLUDED

#include "filter/filter-expr.h"

FilterExprNode *filter_rust_new();
void filter_rust_set_option(FilterExprNode *s, gchar* key, gchar* value);
void filter_rust_set_name(FilterExprNode *s, gchar* name);

#endif
