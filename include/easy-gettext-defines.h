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