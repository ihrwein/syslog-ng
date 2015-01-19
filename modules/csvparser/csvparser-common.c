#include "csvparser-common.h"

inline gint
_is_escape_flag(guint32 flag)
{
  return ((flag & LOG_CSV_PARSER_ESCAPE_MASK) == flag);
}

inline gint
_contains_escape_flag(guint32 flag)
{
  return (flag & LOG_CSV_PARSER_ESCAPE_MASK);
}

inline guint32
_get_escape_flags(guint32 flags)
{
  return (flags & LOG_CSV_PARSER_ESCAPE_MASK);
}

inline guint32
_remove_escape_flags(guint32 flags)
{
  return (flags & (~LOG_CSV_PARSER_ESCAPE_MASK));
}

void
_find_string(gpointer data, gpointer u_data)
{
  const char *item = (const char*) data;
  StrLstPrivData *user_data = (StrLstPrivData*) u_data;

  if (!user_data->first_occurence)
  {
    user_data->first_occurence = strstr(user_data->string, item);
    user_data->delim_length = (user_data->first_occurence) ? strlen(item) : 0;
  }
}

/* searches for str1 in list and returns the first occurence, otherwise NULL */
guchar*
strlst(const char * str1, GList *list, int *delim_length)
{
  StrLstPrivData user_data = {NULL, 0, str1};

  g_list_foreach(list, _find_string, (gpointer) &user_data);

  *delim_length = user_data.delim_length;

  return (guchar*) user_data.first_occurence;
}

inline gboolean
_do_drop_invalid(GList *cur_column, const gchar *src, guint32 flags)
{
  return (cur_column || (src && *src)) && (flags & LOG_CSV_PARSER_DROP_INVALID);
}

inline gboolean
_is_whitespace_char(const gchar* str)
{
  return (*str == ' ' || *str == '\t') ? TRUE : FALSE;
}

inline void
_strip_whitespace_left(const gchar** src)
{
  while (_is_whitespace_char(*src))
    (*src)++;
}

inline gboolean
_check_and_handle_greedy_mode(LogCSVParser *self, GList **cur_column, LogMessage *msg, const gchar **src)
{
 if (*cur_column && (*cur_column)->next == NULL && self->flags & LOG_CSV_PARSER_GREEDY)
   {
     /* greedy mode, the last column gets it all, without taking escaping, quotes or anything into account */
     log_msg_set_value_by_name(msg, (gchar *) (*cur_column)->data, *src, -1);
     *cur_column = NULL;
     *src = NULL;
     return TRUE;
   }
  return FALSE;
}
