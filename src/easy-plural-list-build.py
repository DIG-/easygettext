#!/usr/bin/env python3

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
    print("Maybe sometime...")

if __name__ == "__main__":
  main(sys.argv)