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

#ifndef _EASY_GETTEXT_PLURAL_
#define _EASY_GETTEXT_PLURAL_ 1

#include <stdint.h>

int EasyGettext_evalPlural(EasyGettext*,const uint32_t);  // Struct fully imported, and the number for plural. Return index.
int EasyGettext_parsePlural(EasyGettext*,const char*);    // Struct with translations imported, and locale for future update. Return error code.

#endif