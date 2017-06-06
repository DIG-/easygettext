#ifndef _EASY_GETTEXT_STRUCT_
#define _EASY_GETTEXT_STRUCT_ 1

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