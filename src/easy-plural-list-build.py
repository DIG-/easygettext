#!/usr/bin/env python3

##  Copyright 2017 Gustavo de Oliveira Silva (DIG)
#
#   Licensed under the Apache License, Version 2.0 (the "License");
#   you may not use this file except in compliance with the License.
#   You may obtain a copy of the License at
#
##      http://www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an "AS IS" BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#  See the License for the specific language governing permissions and
#  limitations under the License.
#

import sys
import json
import os.path

def main(argv):
  list = []
  if os.path.isfile("easy-plural-list.json"):
    f = open("easy-plural-list.json","r",encoding="utf-8")
    list = json.load(f)
    f.close()
  
  if len(argv) == 3 :
    if (argv[1] == "--add") or (argv[1] == "-a") :
      if argv[2].replace(' ','') in list :
        print("Already in list.")
      else:
        list.append(argv[2].replace(' ',''))
        f = open("easy-plural-list.json","w",encoding="utf-8")
        json.dump(list,f)
        f.close()
  if (len(argv) == 1) or ((len(argv)==2) and (argv[1] == "--generate" or argv[1] == "-g")) :
    print("Generate file easy-plural-list.c")
    #list.sort()
    f = open("easy-plural-list.c","w",encoding="utf-8")
    f.write("// This is a automatic generated file.\n// Do not edit\n#include \"easy-plural-list.h\"\n#include <string.h>\n")
    f.write("uint32_t EasyGettext_pluralListDecode(const char* str){\n/*uint32_t len = strlen(str);*/\n")
    for (i, parse) in enumerate(list):
      f.write("if(strcmp(str,\"{0}\") == 0) return {1};\n".format(parse,i+1))
    f.write("return 0;\n}\n")
    
    # Add pragma to disable parentheses warning on gcc
    f.write("#ifdef __GNUC__\n#pragma GCC diagnostic push\n#pragma GCC diagnostic ignored \"-Wparentheses\"\n#endif\n")
    
    f.write("int EasyGettext_pluralListEval(const uint32_t opt,const uint32_t n){\nswitch(opt){\ndefault:return 0;\n")
    for (i, parse) in enumerate(list):
      f.write("case {0}: return {1};\n".format(i+1,parse))
    f.write("}\nreturn 0;\n}\n")
    
    # Add pragma to disable parentheses warning on gcc
    f.write("#ifdef __GNUC__\n#pragma GCC diagnostic pop\n#endif\n")
    
    f.close()

if __name__ == "__main__":
  main(sys.argv)