#ifndef _EASY_GETTEXT_
#define _EASY_GETTEXT_ 1

#include "easy-gettext-struct.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

extern EasyGettext EasyGettext_default;

int   EasyGettext_init(EasyGettext*,const char* locale,const char* path);
int   EasyGettext_free(EasyGettext*);
int   EasyGettext_setlocale(EasyGettext*,const char* locale,const char* path);
const char* EasyGettext_gettext(EasyGettext*,const char*);
const char* EasyGettext_ngettext(EasyGettext*,const char*,const char*,const uint64_t);

const int EasyGettext_OK = 0;
const int EasyGettext_MALLOC_FAILED = -1;
const int EasyGettext_INVALID_LOCALE = -2;

#ifdef __cplusplus
}
#endif

#ifdef EASY_GETTEXT_REPLACE
  #undef _
  #define _(A) gettext(A)

  #undef gettext
  #define gettext(A) EasyGettext_gettext(&EasyGettext_default,A)

  #undef ngettext
  #define ngettext(A,B,C) EasyGettext_ngettext(&EasyGettext_default,A,B,C)
#endif

#ifndef EASY_GETTEXT_NO_REDUCTION

  #define EG_(A) EasyGettext_gettext(&EasyGettext_default,A)
  #define EG_N(A,B,C) EasyGettext_ngettext(&EasyGettext_default,A,B,C)
  #define EG_init(A,B) EasyGettext_init(&EasyGettext_default,A,B)
  #define EG_free EasyGettext_free(&EasyGettext_default)

#endif

#endif