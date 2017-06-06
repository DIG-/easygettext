#ifndef _EASY_GETTEXT_STRUCT_
#define _EASY_GETTEXT_STRUCT_ 1

#ifdef __cplusplus
extern "C" {
#endif

typedef struct __attribute__((packed, aligned(4))) {
  // char _private[4*sizeof(char*) + 8];
  #if (defined(__i386)||defined(__i386__)||defined(_M_IX86))
    char _private[16];
  #else
    char _private[24];
  #endif
  
  #ifdef __cplusplus
  #endif
} EasyGettext;

#ifdef __cplusplus
}
#endif

#endif