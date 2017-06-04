#include <easy-gettext.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int EasyGettext_load(EasyGettext* a,const char* locale,const char* path){
  if(a->content != NULL){
    free(a->content);
    a->content = NULL;
  }
  
  if((strlen(locale) != 5)&&(strlen(locale) != 2))
    return EasyGettext_INVALID_LOCALE;
  if((locale[0]<'a')||(locale[0]>'z')||(locale[1]<'a')||(locale[2]>'z'))
    return EasyGettext_INVALID_LOCALE;
  if(strlen(locale) == 5){
    if(locale[2]!='_')
      return EasyGettext_INVALID_LOCALE;
    if((locale[3]<'A')||(locale[3]>'Z')||(locale[4]<'A')||(locale[4]>'Z'))
      return EasyGettext_INVALID_LOCALE;
  }
  
  FILE* file = NULL;
  
  if(path != NULL){
    uint32_t len = strlen(path)+strlen(locale)+5;
    
    char* filename = malloc(len);
    if(filename == NULL)
      return EasyGettext_MALLOC_FAILED;
    memset(filename,0,len);
    strcpy(filename,path);
    strcat(filename,"/");
    strcat(filename,locale);
    strcat(filename,".po");
    file = fopen(filename,"r");
    if(file == NULL){
      memset(filename,0,len);
      strcpy(filename,path);
      strcat(filename,"/");
      strncat(filename,locale,2);
      strcat(filename,".po");
      file = fopen(filename,"r");
    }
    free(filename);
  }
  if(file == NULL){
    // TODO: Find in system directory
    return -99;
  }
  
  
  fclose(file);
  
  return 0;
}

int EasyGettext_init(EasyGettext* a,const char* locale,const char* path){
  a->content = NULL;
  return EasyGettext_load(a,locale,path);
}

int EasyGettext_free(EasyGettext* a){
  if(a->content != NULL){
    free(a->content);
    a->content = NULL;
  }
  return 0;
}

int EasyGettext_setlocale(EasyGettext* a,const char* locale,const char* path){
  return EasyGettext_load(a,locale,path);
}

const char* EasyGettext_gettext(EasyGettext* a,const char* str){
  if(a->content == NULL){
    return str;
  }
  return NULL;
}

const char* EasyGettext_ngettext(EasyGettext* a,const char* str,const char* str2,const uint64_t n){
  if(a->content == NULL){
    return str;
  }
  return NULL;
}