#ifndef _EASY_GETTEXT_PLURAL_
#define _EASY_GETTEXT_PLURAL_ 1

#include "easy-gettext-struct-internal.h"
#include <stdint.h>

int EasyGettext_evalPlural(EasyGettext*,const uint32_t);  // Struct fully imported, and the number for plural. Return index.
int EasyGettext_parsePlural(EasyGettext*,const char*);    // Struct with translations imported, and locale for future update. Return error code.

#endif