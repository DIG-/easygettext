# DIG Makefile modulus
#
# Version:      1.07
# Date:         2016-09-26
#
# Defaults values to makefile

CC=gcc
CXX=g++
LD:=$(CXX)
WINDRES=windres

override CC:=$(PREFIX)$(CC)
override CXX:=$(PREFIX)$(CXX)
override LD:=$(PREFIX)$(LD)
override WINDRES:=$(PREFIX)$(WINDRES)
override CCFLAGS+= -Wall
override CXXFLAGS+= -Wall -std=c++11
LDFLAGS = -Wall 
ifneq ($(MAKECMDGOALS),debug)
override LDFLAGS+=
override CCFLAGS+= -g 
override CXXFLAGS+= -g 
else
override LDFLAGS+= -g 
override CCFLAGS+= -g 
override CXXFLAGS+= -g 
endif

DIR_SRC = src
DIR_OBJ = obj
DIR_BIN = bin
DIR_LIB = lib
DIR_HDR = hdr
DIR_RES = res
DIR_STATIC = static
DIR_SHARED = shared

ifeq (linux,$(findstring linux,$(shell $(CC) -dumpmachine)))
  TGT_WIN=0
  LIB_OS=
else
  ifeq (mingw,$(findstring mingw,$(shell $(CC) -dumpmachine)))
    TGT_WIN=1
    LIB_OS=
    INC_NOWIDE=-I3rdparty/nowide
    LIB_NOWIDE=
    INC_CXXOPTS=-I3rdparty/cxxopts/include
    LIB_CXXOPTS=
    INC_OPENCV=-I../../lib/opencv/build/include
    LIB_OPENCV=-L../../lib/opencv/build/lib -lopencv_features2d320 -lopencv_core320 -lopencv_imgcodecs320 -lopencv_flann320
    INC_LZMA=-I../../lib/lzma1604/C
    LIB_LZMA=-L../../lib/lzma1604/bin -llzma
    INC_DIG_IMAGE_FORMAT=-I./include
    LIB_DIG_IMAGE_FORMAT=-L./lib/shared -ldig-image-format
  endif
endif

ifeq (,$WIN)
$(error Unable to define target. Manually set TGT_WIN=0 or TGT_WIN=1)
endif

override CCFLAGS+=$(INC_NOWIDE)
override CXXFLAGS+=$(INC_NOWIDE)
override LDFLAGS+=$(LIB_NOWIDE)

ifeq ($(OS),Windows_NT)
  L_WIN=1
  RM =del /s /f /q
  COLOR_BLUE =
  COLOR_GREEN=
  COLOR_RED  =
  COLOR_DEF  =
else
  L_WIN=0
  RM =rm -rf
  COLOR_BLUE =\033[1;34m
  COLOR_GREEN=\033[1;32m
  COLOR_RED  =\033[31m
  COLOR_DEF  =\033[0m
endif

DIR_OBJ_STATIC = $(DIR_OBJ)/$(DIR_STATIC)
DIR_OBJ_SHARED = $(DIR_OBJ)/$(DIR_SHARED)
DIR_LIB_STATIC = $(DIR_LIB)/$(DIR_STATIC)
DIR_LIB_SHARED = $(DIR_LIB)/$(DIR_SHARED)

PJ_SRC_WPATH = $(addprefix $(DIR_SRC)/,$(PROJECT_SRC))
PJ_OBJ_WPATH = $(addprefix $(DIR_OBJ)/,$(patsubst %.cpp,%.opp,$(patsubst %.c,%.o,$(PROJECT_SRC))))
ifeq ($(TGT_WIN),1)
#  override PJ_OBJ_WPATH+=$(DIR_OBJ)/resource.o
endif
PJ_OBJ_STATIC_WPATH = $(addprefix $(DIR_OBJ_STATIC)/,$(patsubst %.c,%.o,$(PROJECT_SRC)))
PJ_OBJ_SHARED_WPATH = $(addprefix $(DIR_OBJ_SHARED)/,$(patsubst %.c,%.o,$(PROJECT_SRC)))
PJ_LIB_STATIC_WPATH = $(DIR_LIB_STATIC)/lib$(PROJECT_NAME).a
ifeq ($(TGT_WIN),0)
  PJ_EXE_WPATH = $(DIR_BIN)/$(PROJECT_NAME)
  PJ_LIB_SHARED_WPATH = $(DIR_LIB_SHARED)/lib$(PROJECT_NAME).so
  CCFLAGS_SHARED = $(CCFLAGS) -Iinclude -fpic
  LDFLAGS_SHARED = $(LDFLAGS) -shared
else
  PJ_EXE_WPATH = $(DIR_BIN)/$(PROJECT_NAME).exe
  PJ_LIB_SHARED_WPATH = $(DIR_LIB_SHARED)/$(PROJECT_NAME).dll
  CCFLAGS_SHARED = $(CCFLAGS) -Iinclude
  LDFLAGS_SHARED = $(LDFLAGS) -shared -Wl,--out-implib,$(DIR_LIB_SHARED)/lib$(PROJECT_NAME).a
endif

DIRS = $(abspath $(dir $(PJ_OBJ_WPATH))) $(DIR_BIN)
DIRS_SHARED = $(DIR_OBJ_SHARED) $(DIR_LIB_SHARED)
DIRS_STATIC = $(DIR_OBJ_STATIC) $(DIR_LIB_STATIC)

CCFLAGS_STATIC = $(CCFLAGS) -Iinclude
CXXFLAGS_STATIC = $(CXXFLAGS) -Iinclude

LDFLAGS_STATIC =rcs
