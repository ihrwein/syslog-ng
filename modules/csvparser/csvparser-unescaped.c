#include "csvparser-unescaped.h"

typedef struct _UnescapedParserState {
  guchar *delim;
  guchar *delim_string;
  guchar *delim_char;
  gint delim_len;
} UnescapedParserState;

static inline guchar*
_find_delim_unescaped_quoted(LogCSVParser *self, UnescapedParserState *pstate, const gchar* src, guchar quote)
{
  guchar *delim = NULL;
  guchar *delim_string = NULL;
  guchar *delim_char = NULL;
  gint delim_len = 0;

  /* search for end of quote */
  delim = (guchar *) strchr(src, quote);

  if (delim)
    {
      delim_string = strlst((const char *)delim, self->string_delimiters, &delim_len);
      if (delim_string == (delim + 1) || (strchr(self->delimiters, *(delim + 1)) != NULL ))
        {
          /* closing quote, and then a delimiter, everything is nice */
          delim++;
        }
    }
  else if (!delim)
    {
      /* complete remaining string */
      delim = (guchar *) src + strlen(src);
    }

  pstate->delim = delim;
  pstate->delim_string = delim_string;
  pstate->delim_char = delim_char;
  pstate->delim_len = delim_len;

  return delim;
}

static inline guchar*
_find_delim_unescaped_unquoted(LogCSVParser *self, UnescapedParserState *pstate, const gchar* src)
{
  guchar *delim = NULL;
  guchar *delim_string = NULL;
  guchar *delim_char = NULL;
  gint delim_len = 0;

  if (self->string_delimiters)
    {
      delim_string = strlst(src, self->string_delimiters, &delim_len);
    }

  delim_char = (guchar *) src + strcspn(src, self->delimiters);

  // string delimeter legalabb a karakter delim helyen kezdodik
  if (delim_string && delim_string <= delim_char)
    {
      delim = delim_string;
    }
  else if (delim_char)
    {
      delim = delim_char; 
    }
  else
    {
      delim = (guchar *) src + strlen(src);
    }

  pstate->delim = delim;
  pstate->delim_string = delim_string;
  pstate->delim_char = delim_char;
  pstate->delim_len = delim_len;
  
  return delim;
}

static gint
_get_column_length_unescaped(LogCSVParser *self, const guchar *delim, const gchar *src, guchar quote)
{
  gint len;

  // az oszlop hossza?
  len = delim - (guchar *) src;
  /* move in front of the terminating quote character */
  if (quote && len > 0 && src[len - 1] == quote)
    len--;
  if (len > 0 && self->flags & LOG_CSV_PARSER_STRIP_WHITESPACE)
    {
      while (len > 0 && (_is_whitespace_char(src + len - 1)))
        len--;
    }

  return len;
}

static inline void
_move_to_next_column_unescaped(UnescapedParserState *pstate, const gchar** src)
{
  *src = (gchar *) pstate->delim;

  if (pstate->delim_len && (pstate->delim == pstate->delim_string))
    *src += pstate->delim_len;
  else if (**src)
    (*src)++;
}

static guchar
_get_current_quote_unescaped(LogCSVParser *self, const gchar** src)
{
  guchar *quote = (guchar *) strchr(self->quotes_start, **src);

  if (quote != NULL)
    {
      /* ok, quote character found */
      (*src)++;
      return self->quotes_end[quote - (guchar *) self->quotes_start];
    }
  else
    {
      /* we didn't start with a quote character, no need for escaping, delimiter terminates */
      return  0;
    }
}

static inline guchar*
_find_delim_unescaped(LogCSVParser *self, UnescapedParserState *pstate, const gchar* src, guchar quote)
{
  if (quote)
    {
      return _find_delim_unescaped_quoted(self, pstate, src, quote);
    }
  else
    {
      return _find_delim_unescaped_unquoted(self, pstate, src);
    }
}

gboolean
log_csv_parser_process_unescaped(LogCSVParser *self, LogMessage *msg, const gchar* src)
{
  GList *cur_column = self->super.columns;
  gint len;
  /* no escaping, no need to keep state, we split input and trim if necessary */

  while (cur_column && *src)
    {
      UnescapedParserState pstate = {NULL, NULL, NULL}; 
      guchar current_quote;
      guchar *delim=NULL;

      current_quote = _get_current_quote_unescaped(self, &src);

      if (self->flags & LOG_CSV_PARSER_STRIP_WHITESPACE)
        {
          _strip_whitespace_left(&src);
        }
        
      delim = _find_delim_unescaped(self, &pstate, src, current_quote);

      len = _get_column_length_unescaped(self, delim, src, current_quote);

      if (self->null_value && strncmp(src, self->null_value, len) == 0)
        log_msg_set_value_by_name(msg, (gchar *) cur_column->data, "", 0);
      else
        log_msg_set_value_by_name(msg, (gchar *) cur_column->data, src, len);

      _move_to_next_column_unescaped(&pstate, &src);
      cur_column = cur_column->next;
      _check_and_handle_greedy_mode(self, &cur_column, msg, &src);
    }

  if (_do_drop_invalid(cur_column, src, self->flags))
    {
      /* there are unfilled variables, OR not all of the input was processed
       * and "drop-invalid" flag is specified */
      return FALSE;
    }
  return TRUE;
}
