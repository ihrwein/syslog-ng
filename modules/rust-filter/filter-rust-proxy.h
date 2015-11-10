#ifndef RUST_FILTER_PROXY_H_INCLUDED
#define RUST_FILTER_PROXY_H_INCLUDED

struct RustFilter;

void
rust_filter_free(struct RustFilter* this);

void
rust_filter_set_option(struct RustFilter* this, const gchar* key, const gchar* value);

gboolean
rust_filter_eval(struct RustFilter* this, LogMessage* msg);

void
rust_filter_init(struct RustFilter* s);

struct RustFilter*
rust_filter_new(const gchar* filter_name);


#endif
