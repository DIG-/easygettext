#ifndef _EASY_GETTEXT_STRUCT_
#define _EASY_GETTEXT_STRUCT_ 1

#include <stdint.h>

typedef struct __attribute__((packed, aligned(4))) {
  uint32_t length;
  uint32_t offset;
} EasyGettextLO;

typedef struct __attribute__((packed, aligned(4))) {
  char* content;
  uint32_t number_strings;
  EasyGettextLO* string;
  EasyGettextLO* translation;
  void* polymorph;
  uint32_t type;
} EasyGettext;


#endif