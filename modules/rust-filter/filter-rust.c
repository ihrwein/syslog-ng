#include "filter-rust.h"

#include "logmsg.h"
#include "misc.h"
#include "filter-rust-proxy.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _FilterRust {
  FilterExprNode super;
  gchar* name;
  struct RustFilter* trait;
} FilterRust;

static gboolean
filter_rust_eval(FilterExprNode *s, LogMessage **msgs, gint num_msg)
{
    FilterRust* self = (FilterRust*) s;

    g_assert_cmpint(num_msg, == , 1);

    return rust_filter_eval(self->trait, msgs[0]);   
}

static void
filter_rust_free(FilterExprNode *s)
{
  FilterRust *self = (FilterRust *)s;

  rust_filter_free(self->trait);
  g_free(self->name);
}

void
filter_rust_set_option(FilterExprNode *s, gchar* key, gchar* value)
{    
  FilterRust *self = (FilterRust *)s;

  rust_filter_set_option(self->trait, g_strdup(key), g_strdup(value));
}

void filter_rust_set_name(FilterExprNode *s, gchar* name)
{
  FilterRust *self = (FilterRust *)s;

  if (self->name)
    g_free(self->name);

  self->name = g_strdup(name);

  self->trait = rust_filter_new(self->name);
}

void
filter_rust_init(FilterExprNode *s, GlobalConfig *cfg)
{
  FilterRust *self = (FilterRust *)s;

  // TODO: pass the cfg, too
  rust_filter_init(self->trait);
}

FilterExprNode*
filter_rust_new()
{
  FilterRust *self = (FilterRust*) g_new0(FilterRust, 1);

  filter_expr_node_init_instance(&self->super);    

  self->super.eval = filter_rust_eval;
  self->super.free_fn = filter_rust_free;
  self->super.init = filter_rust_init;

  return &self->super;
}

