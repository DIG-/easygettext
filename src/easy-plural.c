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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "easy-gettext-struct-internal.h"
#include "easy-plural.h"
#include "easy-plural-list.h"
#include "easy-gettext.h"


#ifdef DEBUG_MODE
  #include <inttypes.h>
  #define DBG(msg,...) printf("EGP: "msg, ##__VA_ARGS__)
#else
  #define DBG(...) 
#endif

enum {
  OP_NONE,
  VAL_C,    // Constant by value
  VAL_V,    // Constant by ARG
  CMP_EQ,   // Compare with ==
  CMP_NE,   // Compare with !=
  CMP_LT,   // Compare with <
  CMP_LE,   // Compare with <=
  CMP_GT,   // Compare with >
  CMP_GE,   // Compare with >=
  OP_ADD,   // Operator +
  OP_SUB,   // Operator -
  OP_MUL,   // Operator *
  OP_DIV,   // Operator /
  OP_MOD,   // Operator %
  OP_PAR,   // Operator ()
  OP_AND,   // Operator &&
  OP_OR,    // Operator ||
  BI_AND,   // Binary &
  BI_OR,    // Binary |
  LOG_IF,   // Logical if   X ? Y : Z
};

#ifdef EASYGETTEXT_ENABLE_PLURAL_EVAL
EGP_Node* _EasyGettext_createNode(){
  EGP_Node* tmp = malloc(sizeof(EGP_Node));
  if(tmp != NULL){
    tmp->type=OP_NONE;
    tmp->top = NULL;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->middle = NULL;
  }
  return tmp;
}
#endif

uint8_t _EasyGettext_ctoi(const char c){
  switch(c){
    case '0': return 0;
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;
  }
  return 0;
}

#ifdef EASYGETTEXT_ENABLE_PLURAL_EVAL
uint32_t typeFrom(const char* str){
  if(*str == '+'){
    return OP_ADD;
  }else if(*str == '-'){
    return OP_SUB;
  }else if(*str == '*'){
    return OP_MUL;
  }else if(*str == '/'){
    return OP_DIV;
  }else if(*str == '%'){
    return OP_MOD;
  }else if(*str == '&'){
    if(str[1] == '&')
      return OP_AND;
    return BI_AND;
  }else if(*str == '|'){
    if(str[1] == '|')
      return OP_OR;
    return BI_OR;
  }else if(*str == '<'){
    if(str[1] == '=')
      return CMP_LE;
    return CMP_LT;
  }else if(*str == '>'){
    if(str[1] == '=')
      return CMP_GE;
    return CMP_GT;
  }else if((*str == '=')&&(str[1] == '=')){
    return CMP_EQ;
  }else if((*str == '!')&&(str[1] == '=')){
    return CMP_NE;
  }
  return OP_NONE;
}
#endif

#ifdef DEBUG_MODE
#ifdef EASYGETTEXT_ENABLE_PLURAL_EVAL
void _EasyGettext_recursivePrint(EGP_Node*);
#endif
#endif

#ifdef EASYGETTEXT_ENABLE_PLURAL_EVAL
int _EasyGettext_parsePluralToEval(char* str,EGP_Node** out){
  EGP_Node* base = NULL;
  EGP_Node* actual = _EasyGettext_createNode();
  if(actual == NULL)
    return -1;
  base = actual;

#define CREATE_TMP \
EGP_Node* tmp = _EasyGettext_createNode();\
if(tmp == NULL){\
  /* TODO: Destroy all */\
  return -1;\
}\
DBG(" new Node(%" PRIu64 ")\n",tmp);\

#define INSERT_CONST \
if(actual->type == OP_PAR){\
  if(actual->left != NULL){\
    /* Realy? Inserting a number before operator, but already filled???? */\
    /* TODO: Destroy all */\
    DBG("Vish... %" PRIu64 " -> %" PRIu64 "\n",actual,actual->left);\
    return -2;\
  }\
  DBG("Insert CONST (%"PRIu64") in OP_PAR (%"PRIu64") on left\n",tmp,actual);\
  actual->left = tmp;\
}else if(actual->type!=LOG_IF){\
  if(actual->right != NULL){\
    /* Realy? Inserting a number before operator, but already filled???? */\
    /* TODO: Destroy all */\
    return -2;\
  }\
  DBG("Insert CONST (%"PRIu64") in OP_XX (%"PRIu64") on left\n",tmp,actual);\
  actual->right = tmp;\
}else{\
  if(actual->middle == NULL){\
    DBG("Insert CONST (%"PRIu64") in LOG_IF (%"PRIu64") on middle\n",tmp,actual);\
    actual->middle = tmp;\
  }else if(actual->right == NULL){\
    DBG("Insert CONST (%"PRIu64") in LOG_IF (%"PRIu64") on right\n",tmp,actual);\
    actual->right = tmp;\
  }else{\
    DBG("Insert CONST (%"PRIu64") in LOG_IF (%"PRIu64") on left\n",tmp,actual);\
    /* Realy? Inserting a number before operator, but already filled???? */\
    /* TODO: Destroy all */\
    return -2;\
  }\
}\
tmp->top = actual;\
actual = tmp;

#define INSERT_OPERATOR_COMPARATOR \
CREATE_TMP;\
if(actual->type == OP_NONE){\
  /* Prevent error with expressions starting with operator or comparator. */\
  actual->type = VAL_C;\
  actual->value = 0;\
}\
DBG("Insert %c with  left:%d\n",*str,actual->type);\
tmp->type = typeFrom(str);\
if(actual->top == NULL){\
  tmp->left = actual;\
  actual->top = tmp;\
  actual = tmp;\
  base = actual;\
}else{\
  tmp->left = actual;\
  tmp->top = actual->top;\
  actual->top = tmp;\
  if(tmp->top->left == actual){\
    DBG("insert in left\n");\
    tmp->top->left = tmp;\
  }else if(tmp->top->middle == actual){\
    DBG("insert in middle\n");\
    tmp->top->middle = tmp;\
  }else{\
    DBG("insert in right\n");\
    tmp->top->right = tmp;\
  }\
}\
actual = tmp;

  for(;*str!='\0';str++){
    if(*str == ' ')
      continue;
    DBG("[] %c  %" PRIu64 "\n",*str,actual);
    if((*str >= '0')&&(*str <= '9')){
      // When find constant
      if(actual->type == OP_NONE){
        actual->type = VAL_C;
        actual->value = _EasyGettext_ctoi(*str);
        continue;
      }else if(actual->type == VAL_C){
        actual->value = (10*(actual->value))+_EasyGettext_ctoi(*str);
        continue;
      }else{
        CREATE_TMP;
        tmp->type = VAL_C;
        tmp->value = _EasyGettext_ctoi(*str);
        INSERT_CONST;
        continue;
      }
    }else if((*str == 'N')||(*str == 'n')){
      // When find variable N
      if(actual->type == OP_NONE){
        actual->type = VAL_V;
        continue;
      }else if(actual->type == VAL_C){
        actual->type = VAL_V;
        continue;
      }else if(actual->type == VAL_V){
        actual->type = VAL_V;
        continue;
      }else{
        CREATE_TMP;
        tmp->type = VAL_V;
        INSERT_CONST;
        continue;
      }
    }else if((*str == '+')||(*str == '-')||(*str == '*')||(*str == '/')||(*str == '%')||(*str == '&')||(*str == '|')){
      // When find operator
      INSERT_OPERATOR_COMPARATOR;
      if((tmp->type == OP_AND)||(tmp->type == OP_OR)){
        str++;
      }
      continue;
    }else if((*str == '<')||(*str == '>')||(*str == '!')||(*str == '=')){
      // When find comparator
      INSERT_OPERATOR_COMPARATOR;
      if(!((tmp->type == CMP_LT)||(tmp->type == CMP_GT))){
        str++;
      }
      continue;
    }else if(*str == '('){
      // When find open brackets
      if(actual->type == OP_NONE){
        actual->type = OP_PAR;
      }else if(actual->type == OP_PAR){
        CREATE_TMP;
        tmp->type = OP_PAR;
        tmp->top = actual;
        tmp->left = actual->left;
        actual->left->top = tmp;
        actual->left = tmp;
        actual = tmp;
      }else if(
          (actual->type == OP_ADD)||(actual->type == OP_SUB)||(actual->type == OP_MUL)||(actual->type == OP_DIV)||
          (actual->type == OP_MOD)||(actual->type == OP_AND)||(actual->type == BI_AND)||(actual->type == CMP_EQ)||
          (actual->type == CMP_NE)||(actual->type == CMP_LT)||(actual->type == CMP_LE)||(actual->type == CMP_GT)||
          (actual->type == CMP_GE)||(actual->type == OP_OR)||(actual->type == BI_OR)){
        CREATE_TMP;
        tmp->type = OP_PAR;
        tmp->top = actual;
        actual->right = tmp;
        actual = tmp;
      }
    }else if(*str == ')'){
      while(actual->top != NULL){
        if(actual->top->type == OP_PAR)
          break;
        actual = actual->top;
      }
      if(actual->top != NULL)
        actual = actual->top;
    }else if(*str == '?'){
      CREATE_TMP;
      tmp->type = LOG_IF;
      if(actual->type == OP_NONE){
        actual->type = VAL_C;
        actual->value = 0;
      }
      while(actual->top != NULL){
        if((actual->top->type == OP_PAR)||(actual->top->type == LOG_IF))
          break;
        actual = actual->top;
      }
      if(actual->top == NULL){
        DBG("Put CONST/OP_XX (%"PRIu64") in LOG_IF (%"PRIu64") on left\n",actual,tmp);
        DBG("Insert LOG_IF (%"PRIu64") on BASE\n",tmp);
        tmp->left = actual;
        base = tmp;
        actual = tmp;
      }else if(actual->top->type == OP_PAR){
        tmp->left = actual->left;
        tmp->top = actual;
        actual->left->top = tmp;
        actual->left = tmp;
        actual = tmp;
      }else if(actual->top->type == LOG_IF){
        // Analyse
        if(actual->top->right == NULL){
          DBG("Put CONST/OP_XX (%"PRIu64") in LOG_IF (%"PRIu64") on left\n",actual,tmp);
          DBG("Insert LOG_IF (%"PRIu64") in LOG_IF (%"PRIu64") on middle\n",tmp,actual);
          tmp->left = actual;
          tmp->top = actual->top;
          actual->top->middle = tmp;
          actual->top = tmp;
        }else{
          DBG("Put CONST/OP_XX (%"PRIu64") in LOG_IF (%"PRIu64") on left\n",actual,tmp);
          DBG("Insert LOG_IF (%"PRIu64") in LOG_IF (%"PRIu64") on right\n",tmp,actual);
          tmp->left = actual;
          tmp->top = actual->top;
          actual->top->right = tmp;
          actual->top = tmp;
        }
        actual = tmp;
      }else{
        return -4;
      }
    }else if(*str == ':'){
      while(actual->top != NULL){
        actual = actual->top;
        if((actual->type == LOG_IF)&&(actual->middle != NULL)&&(actual->right == NULL))
          break;
      }
      if((actual->type == LOG_IF)&&(actual->middle != NULL)&&(actual->right == NULL)){
        continue;
      }else{
        // Error!!
        return -5;
      }
    }
  }
  
  #ifdef DEBUG_MODE
  printf("Debugging expression...\n");
  _EasyGettext_recursivePrint(base);
  printf("\n\n");
  #endif
  
  *out = base;
  return 0;
}
#endif

int EasyGettext_parsePlural(EasyGettext* a,const char* locale){
  DBG("parsePlural start.\n");
  if(a->plural != NULL){
    free(a->plural);
    a->plural = NULL;
  }
  a->plural = malloc(sizeof(EasyGettext_Plural));
  if(a->plural == NULL)
    return EasyGettext_MALLOC_FAILED;
  a->plural->type = 0;
  
  DBG("Get first translation string.\n");
  char* str = &(a->content[a->translation[0].offset]);
  DBG("Get first occurence of \"Plural-Forms:\".\n");
  char* plu = strstr(str,"Plural-Forms:");
  if(plu == NULL){
    DBG("Plural-Forms not found!\n");
    free(a->plural);
    a->plural = NULL;
    return 0;
  }
  str = plu;
  DBG("%s\n",plu);
  DBG("Get first occurence of \"nplurals=\".\n");
  plu = strstr(str,"nplurals=");
  if(plu == NULL){
    DBG("nplurals not found!\n");
    free(a->plural);
    a->plural = NULL;
    return 0;
  }
  plu+=9;
  a->plural->total = 0;
  while(1){
    if(plu[0] == ' '){
      plu++;
      continue;
    }
    if((plu[0] == ';')||(plu[0] == '\0')){
      break;
    }
    a->plural->total = (10*(a->plural->total))+_EasyGettext_ctoi(*plu);
    plu++;
  }
  DBG("Found nplurals. Value = %d\n",a->plural->total);
  
  DBG("Get first occurence of \"plural=\".\n");
  plu = strstr(str,"plural=");
  if(plu == NULL){
    DBG("Plural expression not found!\n");
    free(a->plural);
    a->plural = NULL;
    return 0;
  }
  str = plu+7;
  DBG("Found plural. Get first occurence of \";\".\n");
  plu = strstr(str,";");
  if(plu == NULL){
    DBG("Invalid plural expression!\n");
    free(a->plural);
    a->plural = NULL;
    return 0;
  }
  DBG("Create temporary string.\n");
  char* tmp = malloc(1+plu-str);
  if(tmp == NULL){
    free(a->plural);
    a->plural = NULL;
    return EasyGettext_MALLOC_FAILED;
  }
  memset(tmp,0,1+plu-str);
  DBG("Copy plural into new string.\n");
  int i = 0;
  for(;str<plu;str++){
    if((*str == ' ')||(*str == '\\')||(*str == '\n')||(*str == '\r'))
      continue;
    if(*str == ';')
      break;
    tmp[i++] = *str;
  }
  DBG("Copied.. \"%s\"\n",tmp);
  DBG("Parse plural with internal defines.\n");
  a->plural->type = EasyGettext_pluralListDecode(tmp);
  if(a->plural->type == 0){
    #ifdef EASYGETTEXT_ENABLE_PLURAL_EVAL
    DBG("Start parsing string\n");
    _EasyGettext_parsePluralToEval(tmp,&(a->plural->expression));
    #else
    DBG("Plural eval was not enabled at compilation.\n");
    #endif
  }else{
    DBG("Using internal defines for plural expression.\n");
  }
  DBG("done\n");
  return 0;
}

#ifdef EASYGETTEXT_ENABLE_PLURAL_EVAL
int _EasyGettext_recursiveEval(const EGP_Node* node, const uint32_t n){
  #define re_L _EasyGettext_recursiveEval(node->left,n)
  #define re_R _EasyGettext_recursiveEval(node->right,n)
  #define re_M _EasyGettext_recursiveEval(node->middle,n)
  switch(node->type){
    default:
      return 0;
    case VAL_C:   return (node->value);
    case VAL_V:   return (n);
    case OP_PAR:  return (re_L);
    case OP_ADD:  return (re_L+re_R);
    case OP_SUB:  return (re_L-re_R);
    case OP_MUL:  return (re_L*re_R);
    case OP_DIV:  return (re_L/re_R);
    case OP_MOD:  return (re_L%re_R);
    case OP_AND:  return (re_L&&re_R);
    case OP_OR:   return (re_L||re_R);
    case BI_AND:  return (re_L&re_R);
    case BI_OR:   return (re_L|re_R);
    case CMP_EQ:  return (re_L==re_R);
    case CMP_NE:  return (re_L!=re_R);
    case CMP_LT:  return (re_L<re_R);
    case CMP_LE:  return (re_L<=re_R);
    case CMP_GT:  return (re_L>re_R);
    case CMP_GE:  return (re_L>=re_R);
    case LOG_IF:  return (re_L?re_M:re_R);
  }
  return 0;
  #undef re_L
  #undef re_R
  #undef re_M
}
#endif

int EasyGettext_evalPlural(EasyGettext* a,const uint32_t n){
  if(a == NULL)
    return 0;
  if(a->plural == NULL)
    return 0;
  int e = 0;
  if(a->plural->type != 0){
    e = EasyGettext_pluralListEval(a->plural->type,n);
  }else{
    #ifdef EASYGETTEXT_ENABLE_PLURAL_EVAL
    if(a->plural->expression == NULL)
      return 0;
    e = _EasyGettext_recursiveEval(a->plural->expression,n);
    DBG("_EasyGettext_recursiveEval = %d\n",e);
    #else
    return 0;
    #endif
  }
  
  if(e > a->plural->total)
    e = 0;
  if(e < 0){
    DBG("Invalid value");
    e = 0;
  }
  return e;
}

// For debug purpose only
#ifdef DEBUG_MODE
#ifdef EASYGETTEXT_ENABLE_PLURAL_EVAL
void _EasyGettext_recursivePrint(EGP_Node* n){
  //DBG("\n[]%d\n",n->type);
  if(n->type == VAL_C){
    printf("%d",n->value);
    return;
  }
  if(n->type == VAL_V){
    printf("n");
    return;
  }
  if(n->type == OP_PAR){
    printf("(");
  }
  _EasyGettext_recursivePrint(n->left);
  switch(n->type){
    case CMP_EQ: printf("=="); break;
    case CMP_NE: printf("!="); break;
    case CMP_LT: printf("<"); break;
    case CMP_LE: printf("<="); break;
    case CMP_GT: printf(">"); break;
    case CMP_GE: printf(">="); break;
    case OP_ADD: printf("+"); break;
    case OP_SUB: printf("-"); break;
    case OP_MUL: printf("*"); break;
    case OP_DIV: printf("/"); break;
    case OP_MOD: printf("%%"); break;
    case OP_AND: printf("&&"); break;
    case OP_OR:  printf("||"); break;
    case BI_AND: printf("&"); break;
    case BI_OR:  printf("|"); break;
    case LOG_IF: printf("?"); break;
    case OP_PAR: printf(")"); return;
  }
  if(n->type == LOG_IF){
    _EasyGettext_recursivePrint(n->middle);
    printf(":");
  }
  _EasyGettext_recursivePrint(n->right);
}
#endif
#endif