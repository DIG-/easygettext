#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EASY_GETTEXT_REPLACE
#define EASY_GETTEXT_STATIC
#include "easy-gettext.h"

#define USERNAME "DIG"
#define CODE_LINES 18

int main(int argc,char** argv){
  {
    int r;
    if(argc > 1){
      r = EG_init(argv[1],"../example");
    }else{
      r = EG_init("pt_BR","../example");
    }
    if(r == EasyGettext_INVALID_LOCALE){
      printf("Invalid Locale.\n");
    }else if(r == EasyGettext_LOCALE_NOT_FOUND){
      printf("Locale not found.\n");
    }else if(r == EasyGettext_MALLOC_FAILED){
      printf("Error while allocating memory.\n");
    }else if(r == EasyGettext_ERROR_WHILE_READING_TRANSLATION_FILE){
      printf("Error while reading translation file.\n");
    }
  }
  
  printf(_("This is a simple EasyGettext example\n"));
  printf(_("Hi I'm %s.\nNice to meet you.\n"),USERNAME);
  printf(EG_("I present you the file \"%s\" with some examples.\n"),__FILE__);
  printf(gettext("With this example you will be able to understand how to use gettext\nand how to use this library.\n"));
  printf(ngettext("This file has %d line.","This file has %d lines.", CODE_LINES),CODE_LINES);
  
  EG_free();
  return 0;
}