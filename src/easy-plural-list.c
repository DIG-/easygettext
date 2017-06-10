// This is a automatic generated file.
// Do not edit
#include "easy-plural-list.h"
#include <string.h>
uint32_t EasyGettext_pluralListDecode(const char* str){
/*uint32_t len = strlen(str);*/
if(strcmp(str,"(n>1)") == 0) return 1;
if(strcmp(str,"(n!=1)") == 0) return 2;
if(strcmp(str,"n!=1") == 0) return 3;
if(strcmp(str,"n>1") == 0) return 4;
if(strcmp(str,"(n==0?0:n==1?1:n==2?2:n%100>=3&&n%100<=10?3:n%100>=11?4:5)") == 0) return 5;
if(strcmp(str,"n==0?0:n==1?1:n==2?2:n%100>=3&&n%100<=10?3:n%100>=11?4:5") == 0) return 6;
if(strcmp(str,"0") == 0) return 7;
if(strcmp(str,"(n%10==1&&n%100!=11?0:n%10>=2&&n%10<=4&&(n%100<10||n%100>=20)?1:2)") == 0) return 8;
if(strcmp(str,"n%10==1&&n%100!=11?0:n%10>=2&&n%10<=4&&(n%100<10||n%100>=20)?1:2") == 0) return 9;
if(strcmp(str,"(n==1)?0:(n>=2&&n<=4)?1:2") == 0) return 10;
if(strcmp(str,"(n==1)?0:n%10>=2&&n%10<=4&&(n%100<10||n%100>=20)?1:2") == 0) return 11;
if(strcmp(str,"(n==1)?0:(n==2)?1:(n!=8&&n!=11)?2:3") == 0) return 12;
if(strcmp(str,"n==1?0:n==2?1:(n>2&&n<7)?2:(n>6&&n<11)?3:4") == 0) return 13;
if(strcmp(str,"(n==1||n==11)?0:(n==2||n==12)?1:(n>2&&n<20)?2:3") == 0) return 14;
if(strcmp(str,"(n%10!=1||n%100==11)") == 0) return 15;
if(strcmp(str,"n%10!=1||n%100==11") == 0) return 16;
if(strcmp(str,"(n!=0)") == 0) return 17;
if(strcmp(str,"n!=0") == 0) return 18;
if(strcmp(str,"(n==1)?0:(n==2)?1:(n==3)?2:3") == 0) return 19;
if(strcmp(str,"(n%10==1&&n%100!=11?0:n%10>=2&&(n%100<10||n%100>=20)?1:2)") == 0) return 20;
if(strcmp(str,"n%10==1&&n%100!=11?0:n%10>=2&&(n%100<10||n%100>=20)?1:2") == 0) return 21;
if(strcmp(str,"(n%10==1&&n%100!=11?0:n!=0?1:2)") == 0) return 22;
if(strcmp(str,"n%10==1&&n%100!=11?0:n!=0?1:2") == 0) return 23;
if(strcmp(str,"n==1||n%10==1?0:1") == 0) return 24;
if(strcmp(str,"(n==0?0:n==1?1:2)") == 0) return 25;
if(strcmp(str,"n==0?0:n==1?1:2") == 0) return 26;
if(strcmp(str,"(n==1?0:n==0||(n%100>1&&n%100<11)?1:(n%100>10&&n%100<20)?2:3)") == 0) return 27;
if(strcmp(str,"n==1?0:n==0||(n%100>1&&n%100<11)?1:(n%100>10&&n%100<20)?2:3") == 0) return 28;
if(strcmp(str,"(n==1?0:n%10>=2&&n%10<=4&&(n%100<10||n%100>=20)?1:2)") == 0) return 29;
if(strcmp(str,"n==1?0:n%10>=2&&n%10<=4&&(n%100<10||n%100>=20)?1:2") == 0) return 30;
if(strcmp(str,"(n==1?0:(n==0||(n%100>0&&n%100<20))?1:2)") == 0) return 31;
if(strcmp(str,"n==1?0:(n==0||(n%100>0&&n%100<20))?1:2") == 0) return 32;
if(strcmp(str,"n==1?0:(n>=2&&n<=4)?1:2") == 0) return 33;
if(strcmp(str,"(n%100==1?0:n%100==2?1:n%100==3||n%100==4?2:3)") == 0) return 34;
if(strcmp(str,"n%100==1?0:n%100==2?1:n%100==3||n%100==4?2:3") == 0) return 35;
if(strcmp(str,"n!=1?1:0") == 0) return 36;
if(strcmp(str,"n>1?1:0") == 0) return 37;
if(strcmp(str,"n%10==1&&n%100!=11?1:n!=0?2:0") == 0) return 38;
if(strcmp(str,"n==1||n==11?0:n==2||n==12?1:n>0&&n<20?2:3") == 0) return 39;
if(strcmp(str,"n==1?0:n==0||n%100>0&&n%100<20?1:2") == 0) return 40;
if(strcmp(str,"n%10==1&&n%100!=11?0:n%10>=2&&(n%100<10||n%100>=20)?2:1") == 0) return 41;
if(strcmp(str,"n==1?0:n>=2&&n<=4?1:2") == 0) return 42;
if(strcmp(str,"n==1?0:n==2?1:n>=3&&n<=6?2:n>=7&&n<=10?3:4") == 0) return 43;
if(strcmp(str,"n==0?5:n==1?0:n==2?1:n%100>=3&&n%100<=10?2:n%100>=11&&n%100<=99?3:4") == 0) return 44;
if(strcmp(str,"n==1?0:n==0||n%100>0&&n%100<=10?1:n%100>10&&n%100<20?2:3") == 0) return 45;
if(strcmp(str,"n%10==1?0:n%10==2?1:2") == 0) return 46;
if(strcmp(str,"n%10==1&&n%100!=11?0:1") == 0) return 47;
if(strcmp(str,"n%10==1&&n%100!=11&&n%100!=71&&n%100!=91?0:n%10==2&&n%100!=12&&n%100!=72&&n%100!=92?1:(n%10==3||n%10==4||n%10==9)&&n%100!=13&&n%100!=14&&n%100!=19&&n%100!=73&&n%100!=74&&n%100!=79&&n%100!=93&&n%100!=94&&n%100!=99?2:n%1000000==0&&n!=0?3:4") == 0) return 48;
return 0;
}
#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wparentheses"
#endif
int EasyGettext_pluralListEval(const uint32_t opt,const uint32_t n){
switch(opt){
default:return 0;
case 1: return (n>1);
case 2: return (n!=1);
case 3: return n!=1;
case 4: return n>1;
case 5: return (n==0?0:n==1?1:n==2?2:n%100>=3&&n%100<=10?3:n%100>=11?4:5);
case 6: return n==0?0:n==1?1:n==2?2:n%100>=3&&n%100<=10?3:n%100>=11?4:5;
case 7: return 0;
case 8: return (n%10==1&&n%100!=11?0:n%10>=2&&n%10<=4&&(n%100<10||n%100>=20)?1:2);
case 9: return n%10==1&&n%100!=11?0:n%10>=2&&n%10<=4&&(n%100<10||n%100>=20)?1:2;
case 10: return (n==1)?0:(n>=2&&n<=4)?1:2;
case 11: return (n==1)?0:n%10>=2&&n%10<=4&&(n%100<10||n%100>=20)?1:2;
case 12: return (n==1)?0:(n==2)?1:(n!=8&&n!=11)?2:3;
case 13: return n==1?0:n==2?1:(n>2&&n<7)?2:(n>6&&n<11)?3:4;
case 14: return (n==1||n==11)?0:(n==2||n==12)?1:(n>2&&n<20)?2:3;
case 15: return (n%10!=1||n%100==11);
case 16: return n%10!=1||n%100==11;
case 17: return (n!=0);
case 18: return n!=0;
case 19: return (n==1)?0:(n==2)?1:(n==3)?2:3;
case 20: return (n%10==1&&n%100!=11?0:n%10>=2&&(n%100<10||n%100>=20)?1:2);
case 21: return n%10==1&&n%100!=11?0:n%10>=2&&(n%100<10||n%100>=20)?1:2;
case 22: return (n%10==1&&n%100!=11?0:n!=0?1:2);
case 23: return n%10==1&&n%100!=11?0:n!=0?1:2;
case 24: return n==1||n%10==1?0:1;
case 25: return (n==0?0:n==1?1:2);
case 26: return n==0?0:n==1?1:2;
case 27: return (n==1?0:n==0||(n%100>1&&n%100<11)?1:(n%100>10&&n%100<20)?2:3);
case 28: return n==1?0:n==0||(n%100>1&&n%100<11)?1:(n%100>10&&n%100<20)?2:3;
case 29: return (n==1?0:n%10>=2&&n%10<=4&&(n%100<10||n%100>=20)?1:2);
case 30: return n==1?0:n%10>=2&&n%10<=4&&(n%100<10||n%100>=20)?1:2;
case 31: return (n==1?0:(n==0||(n%100>0&&n%100<20))?1:2);
case 32: return n==1?0:(n==0||(n%100>0&&n%100<20))?1:2;
case 33: return n==1?0:(n>=2&&n<=4)?1:2;
case 34: return (n%100==1?0:n%100==2?1:n%100==3||n%100==4?2:3);
case 35: return n%100==1?0:n%100==2?1:n%100==3||n%100==4?2:3;
case 36: return n!=1?1:0;
case 37: return n>1?1:0;
case 38: return n%10==1&&n%100!=11?1:n!=0?2:0;
case 39: return n==1||n==11?0:n==2||n==12?1:n>0&&n<20?2:3;
case 40: return n==1?0:n==0||n%100>0&&n%100<20?1:2;
case 41: return n%10==1&&n%100!=11?0:n%10>=2&&(n%100<10||n%100>=20)?2:1;
case 42: return n==1?0:n>=2&&n<=4?1:2;
case 43: return n==1?0:n==2?1:n>=3&&n<=6?2:n>=7&&n<=10?3:4;
case 44: return n==0?5:n==1?0:n==2?1:n%100>=3&&n%100<=10?2:n%100>=11&&n%100<=99?3:4;
case 45: return n==1?0:n==0||n%100>0&&n%100<=10?1:n%100>10&&n%100<20?2:3;
case 46: return n%10==1?0:n%10==2?1:2;
case 47: return n%10==1&&n%100!=11?0:1;
case 48: return n%10==1&&n%100!=11&&n%100!=71&&n%100!=91?0:n%10==2&&n%100!=12&&n%100!=72&&n%100!=92?1:(n%10==3||n%10==4||n%10==9)&&n%100!=13&&n%100!=14&&n%100!=19&&n%100!=73&&n%100!=74&&n%100!=79&&n%100!=93&&n%100!=94&&n%100!=99?2:n%1000000==0&&n!=0?3:4;
}
return 0;
}
#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif
