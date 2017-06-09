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

#ifndef _EASY_GETTEXT_STRUCT_
#define _EASY_GETTEXT_STRUCT_ 1

#ifndef _EASY_GETTEXT_COMPILE_TIME_
#error Does not include this file directly.
#endif

#include <stdint.h>

typedef struct EGP_Node {
  uint32_t type;
  uint32_t value;
  struct EGP_Node *top,*left,*right,*middle;
} EGP_Node;

typedef struct {
  uint8_t total;
  EGP_Node* expression;
} EasyGettext_Plural;

typedef struct __attribute__((packed, aligned(4))) {
  uint32_t length;
  uint32_t offset;
} EasyGettextLO;

typedef struct __attribute__((packed, aligned(4))) {
  char* content;
  uint32_t number_strings;
  EasyGettextLO* string;
  EasyGettextLO* translation;
  EasyGettext_Plural* plural;
  void* polymorph;
  uint32_t type;
} EasyGettext;


#endif