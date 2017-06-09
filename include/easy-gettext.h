/**
 **  Copyright 2017 Gustavo de Oliveira Silva (DIG)
 **
 **  Licensed under the Apache License, Version 2.0 (the "License");
 **  you may not use this file except in compliance with the License.
 **  You may obtain a copy of the License at
 **
 **      http://www.apache.org/licenses/LICENSE-2.0
 **
 **  Unless required by applicable law or agreed to in writing, software
 **  distributed under the License is distributed on an "AS IS" BASIS,
 **  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 **  See the License for the specific language governing permissions and
 **  limitations under the License.
 **
 */

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