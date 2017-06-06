#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "easy-gettext-struct-internal.h"
#include "easy-gettext.h"
#include "easy-plural.h"
#include "version.h"

#ifdef DEBUG_MODE
  #include <inttypes.h>
  #define DBG(msg,...) printf("EG: "msg, ##__VA_ARGS__)
#else
  #define DBG(...) 
#endif

/**
 * These values are extracted from
 * https://www.gnu.org/software/gettext/manual/html_node/MO-Files.html 
 * at 2017-06-04
 */
#define POFILE_OFFSET_MAGIC_NUMBER 0
#define POFILE_OFFSET_FILE_FORMAT_REV 4
#define POFILE_OFFSET_NUMBER_STRINGS 8
#define POFILE_OFFSET_TABLE_STRINGS 12
#define POFILE_OFFSET_TABLE_TRANSLATIONS 16
#define POFILE_OFFSET_SIZE_HASH 20
#define POFILE_OFFSET_TABLE_HASH 24
// End of Values

#define TYPE_SORT 0
#define TYPE_HASH 1

EasyGettext EasyGettext_default;
char* EasyGettext_version = EASY_GETTEXT_VERSION;

uint32_t ChangeEndianess(const uint32_t a){
  return ((a&0xff)<<24)|((a&0xff00)<<8)|((a&0xff0000)>>8)|((a&0xff000000)>>24);
}

int EasyGettext_load(EasyGettext* a,const char* locale,const char* path){
  if(a->content != NULL){
    free(a->content);
    a->content = NULL;
  }
  
  // Interpret Locale string
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
  
  // Search for translation file
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
    strcat(filename,".mo");
    file = fopen(filename,"rb");
    if(file == NULL){
      memset(filename,0,len);
      strcpy(filename,path);
      strcat(filename,"/");
      strncat(filename,locale,2);
      strcat(filename,".mo");
      file = fopen(filename,"rb");
    }
    free(filename);
  }
  if(file == NULL){
    // TODO: Find in system directory
    return EasyGettext_LOCALE_NOT_FOUND;
  }
  
  // Read file content
  {
    uint64_t filesize;
    fseek(file,0,SEEK_END);
    filesize = ftell(file);
    fseek(file,0,SEEK_SET);
    a->content = malloc(filesize);
    if(a->content == NULL)
      return EasyGettext_MALLOC_FAILED;
    if(fread(a->content,1,filesize,file) != filesize){
      free(a->content);
      a->content = NULL;
      return EasyGettext_ERROR_WHILE_READING_TRANSLATION_FILE;
    }
  }
  fclose(file);
  
  // Import structure of MO file
  {
    uint8_t change_endianess = 0;
    uint32_t magic_number = *((uint32_t*)((a->content)+POFILE_OFFSET_MAGIC_NUMBER));
    if(magic_number != 2500072158 /*0x950412de*/){
      change_endianess = 1;
    }
    a->number_strings = *((uint32_t*)((a->content)+POFILE_OFFSET_NUMBER_STRINGS));
    if(change_endianess){
      a->number_strings = ChangeEndianess(a->number_strings);
    }
    uint32_t offset = *((uint32_t*)((a->content)+POFILE_OFFSET_TABLE_STRINGS));
    if(change_endianess){
      offset = ChangeEndianess(offset);
    }
    a->string = (EasyGettextLO*)&(a->content[offset]);
    offset = *((uint32_t*)((a->content)+POFILE_OFFSET_TABLE_TRANSLATIONS));
    if(change_endianess){
      offset = ChangeEndianess(offset);
    }
    a->translation = (EasyGettextLO*)&(a->content[offset]);
    if(change_endianess){
      uint32_t i=0;
      for(;i<a->number_strings;i++){
        a->string[i].length = ChangeEndianess(a->string[i].length);
        a->string[i].offset = ChangeEndianess(a->string[i].offset);
        a->translation[i].length = ChangeEndianess(a->translation[i].length);
        a->translation[i].offset = ChangeEndianess(a->translation[i].offset);
      }
    }
  }
  
  /*int e = */EasyGettext_parsePlural(a,locale);
  
  // TODO: Other type for search process
  a->type = TYPE_SORT;
  a->polymorph = NULL;
  
  return 0;
}

int EasyGettext_init(EasyGettext* a,const char* locale,const char* path){
  a->content = NULL;
  a->polymorph = NULL;
  a->plural = NULL;
  return EasyGettext_load(a,locale,path);
}

int EasyGettext_free(EasyGettext* a){
  if(a->content != NULL){
    free(a->content);
    a->content = NULL;
  }
  if(a->polymorph != NULL){
    free(a->polymorph);
    a->polymorph = NULL;
  }
  return 0;
}

int EasyGettext_setlocale(EasyGettext* a,const char* locale,const char* path){
  EasyGettext_free(a);
  return EasyGettext_load(a,locale,path);
}

const char* EasyGettext_gettext(EasyGettext* a,const char* str){
  if((a->content == NULL)||(a->number_strings == 0)){
    return str;
  }
  
  if(a->type == TYPE_SORT){
    // Search using Sorted basics
    uint32_t len = strlen(str);
    uint32_t l=0,r=(a->number_strings-1);
    uint32_t p;
    int cmp;
    while(1){
      if(l>r)
        return str;
      p=((r+l)/2)+(r+l)%2;
      cmp = strncmp(str,&(a->content[a->string[p].offset]),a->string[p].length<len?a->string[p].length:len);
      // <0 if str is before P
      // >0 if str is after P
      if(cmp < 0){
        r = p-1;
      }else if(cmp > 0){
        l = p+1;
      }else{
        // Assuming  AA < AAA < AAB < AABC < AAC
        if(len > strlen(&(a->content[a->string[p].offset]))){
          r = p-1;
        }else if(len < strlen(&(a->content[a->string[p].offset]))){
          l = p+1;
        }else{
          return &(a->content[a->translation[p].offset]);
        }
      }
    }
  }
  // If unimplemented type, return str
  return str;
}

const char* EasyGettext_ngettext(EasyGettext* a,const char* str,const char* str2,const uint32_t n){
  char* base = (char*)EasyGettext_gettext(a,str);
  if((base == str)||(base == NULL)){
    return str2;
  }
  
  int i = EasyGettext_evalPlural(a,n);
  while(i-- > 0){
    while(*base != '\0'){
      base++;
    }
    base++;
  }
  
  return base;
}