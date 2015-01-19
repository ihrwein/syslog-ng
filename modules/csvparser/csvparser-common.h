#ifndef CSVPARSER_COMMON_H_INCLUDED
#define CSVPARSER_COMMON_H_INCLUDED

#include "parser/parser-expr.h"

#define LOG_CSV_PARSER_ESCAPE_NONE        0x0001
#define LOG_CSV_PARSER_ESCAPE_BACKSLASH   0x0002
#define LOG_CSV_PARSER_ESCAPE_DOUBLE_CHAR 0x0004
#define LOG_CSV_PARSER_ESCAPE_MASK        0x0007
#define LOG_CSV_PARSER_STRIP_WHITESPACE   0x0008
#define LOG_CSV_PARSER_GREEDY             0x0010
#define LOG_CSV_PARSER_DROP_INVALID       0x0020

#define LOG_CSV_PARSER_FLAGS_DEFAULT  ((LOG_CSV_PARSER_STRIP_WHITESPACE) | (LOG_CSV_PARSER_ESCAPE_NONE))


typedef struct _LogCSVParser
{
  LogColumnParser super;
  gchar *delimiters;
  gchar *quotes_start;
  gchar *quotes_end;
  gchar *null_value;
  guint32 flags;
  GList *string_delimiters;
} LogCSVParser;


inline gint
_is_escape_flag(guint32 flag);

inline gint
_contains_escape_flag(guint32 flag);

inline guint32
_get_escape_flags(guint32 flags);

inline guint32
_remove_escape_flags(guint32 flags);

typedef struct _StrLstPrivData {
  char *first_occurence;
  int delim_length;
  const char *string;
} StrLstPrivData;

void
_find_string(gpointer data, gpointer u_data);

/* searches for str1 in list and returns the first occurence, otherwise NULL */
guchar*
strlst(const char * str1, GList *list, int *delim_length);

inline gboolean
_do_drop_invalid(GList *cur_column, const gchar *src, guint32 flags);

inline gboolean
_is_whitespace_char(const gchar* str);

inline void
_strip_whitespace_left(const gchar** src);


inline gboolean
_check_and_handle_greedy_mode(LogCSVParser *self, GList **cur_column, LogMessage *msg, const gchar **src);

#endif
