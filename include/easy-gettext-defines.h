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

#ifndef _EASY_GETTEXT_DEFINES_
#define _EASY_GETTEXT_DEFINES_ 1

#ifndef _EASY_GETTEXT_COMPILE_TIME_
typedef void* EasyGettext;
#endif

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

#ifndef EASY_GETTEXT_NO_REPLACE
  #ifdef _
    #undef _
  #endif
  #define _(A) EasyGettext_gettext(&EasyGettext_default,A)
  
  #ifdef gettext
    #undef gettext
  #endif
  #define gettext(A) EasyGettext_gettext(&EasyGettext_default,A)

  #ifdef ngettext
    #undef ngettext
  #endif
  #define ngettext(A,B,C) EasyGettext_ngettext(&EasyGettext_default,A,B,C)
#endif

#ifndef EASY_GETTEXT_NO_REDUCTION
  #define EG_(A) EasyGettext_gettext(&EasyGettext_default,A)
  #define EG_N(A,B,C) EasyGettext_ngettext(&EasyGettext_default,A,B,C)
  #define EG_init(A,B) EasyGettext_init(&EasyGettext_default,A,B)
  #define EG_clean() EasyGettext_clean(&EasyGettext_default)
#endif

#endif