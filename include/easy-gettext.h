#ifndef _EASY_GETTEXT_
#define _EASY_GETTEXT_ 1

#include "easy-gettext-defines.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

_EAG_PUB_ extern char* EasyGettext_version;
_EAG_PUB_ extern EasyGettext EasyGettext_default;

_EAG_PUB_          int  EasyGettext_init(EasyGettext*,const char* locale,const char* path);
_EAG_PUB_          int  EasyGettext_clean(EasyGettext*);

_EAG_PUB_ EasyGettext*  EasyGettext_create();
_EAG_PUB_         void  EasyGettext_free(EasyGettext*);

_EAG_PUB_          int  EasyGettext_setlocale(EasyGettext*,const char* locale,const char* path);
_EAG_PUB_  const char*  EasyGettext_gettext(EasyGettext*,const char*);
_EAG_PUB_  const char*  EasyGettext_ngettext(EasyGettext*,const char*,const char*,const uint32_t);

static const int EasyGettext_OK = 0;
static const int EasyGettext_MALLOC_FAILED = -1;
static const int EasyGettext_INVALID_LOCALE = -2;
static const int EasyGettext_LOCALE_NOT_FOUND = -3;
static const int EasyGettext_ERROR_WHILE_READING_TRANSLATION_FILE = -4;

#ifdef __cplusplus
}
#endif

#endif