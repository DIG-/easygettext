#ifndef _EASY_GETTEXT_
#define _EASY_GETTEXT_ 1

#ifndef _EASY_GETTEXT_COMPILE_TIME_
#include "easy-gettext-struct.h"
#endif
#include <stdint.h>

/**
 * 
 */
#ifdef EASY_GETTEXT_STATIC
  #define _EAG_LOC_ 
  #define _EAG_PUB_ 
#elif defined _WIN32 || defined __CYGWIN__ || defined _WIN64
  #define _EAG_LOC_ 
  #ifdef _EASY_GETTEXT_COMPILE_TIME_
    #define _EAG_PUB_ __declspec(dllexport)
  #else
    #define _EAG_PUB_ __declspec(dllimport)
  #endif
#else
  #if __GNUC__ >= 4
    #define _EAG_PUB_ __attribute__ ((visibility ("default")))
    #define _EAG_LOC_  __attribute__ ((visibility ("hidden")))
  #else
    #define _EAG_PUB_
    #define _EAG_LOC_
  #endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

_EAG_PUB_ extern EasyGettext EasyGettext_default;

_EAG_PUB_ int   EasyGettext_init(EasyGettext*,const char* locale,const char* path);
_EAG_PUB_ int   EasyGettext_free(EasyGettext*);
_EAG_PUB_ int   EasyGettext_setlocale(EasyGettext*,const char* locale,const char* path);
_EAG_PUB_ const char* EasyGettext_gettext(EasyGettext*,const char*);
_EAG_PUB_ const char* EasyGettext_ngettext(EasyGettext*,const char*,const char*,const uint64_t);

static const int EasyGettext_OK = 0;
static const int EasyGettext_MALLOC_FAILED = -1;
static const int EasyGettext_INVALID_LOCALE = -2;
static const int EasyGettext_LOCALE_NOT_FOUND = -3;
static const int EasyGettext_ERROR_WHILE_READING_TRANSLATION_FILE = -4;

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
  #define EG_free() EasyGettext_free(&EasyGettext_default)

#endif

#endif