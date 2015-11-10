/*
 * Copyright (c) 2002-2014 BalaBit S.a.r.l.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * As an additional exemption you are allowed to compile & link against the
 * OpenSSL libraries as published by the OpenSSL project. See the file
 * COPYING for details.
 *
 */

#include "cfg-parser.h"
#include "filter/filter-expr.h"
#include "filter-rust-grammar.h"

extern int filter_rust_debug;

int filter_rust_parse(CfgLexer *lexer, FilterExprNode **instance, gpointer arg);

static CfgLexerKeyword filter_rust_keywords[] = {
  { "rust",     KW_RUST },
  { "option",   KW_OPTION },
  { "filter_subtype",   KW_FILTER_SUBTYPE },
  { NULL }
};
 
CfgParser filter_rust_parser =
{
#if ENABLE_DEBUG
  .debug_flag = &filter_rust_debug,
#endif
  .name = "filter-rust",
  .keywords = filter_rust_keywords,
  .parse = (gint (*)(CfgLexer *, gpointer *, gpointer)) filter_rust_parse,
  .cleanup = (void (*)(gpointer)) log_pipe_unref,
};

CFG_PARSER_IMPLEMENT_LEXER_BINDING(filter_rust_, FilterExprNode **)

