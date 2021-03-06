# DIG Makefile modulus
#
# Version:      1.10
# Date:         2017-06-04
#
# Defaults values to makefile

CC=gcc
CXX=g++
LD:=$(CXX)
WINDRES=windres

override CC:=$(PREFIX)$(CC)
override CXX:=$(PREFIX)$(CXX)
override LD:=$(PREFIX)$(LD)

DIR_SRC = src
DIR_OBJ = obj
DIR_BIN = bin
DIR_LIB = lib
DIR_HDR = hdr
DIR_RES = res
DIR_STATIC = static
DIR_SHARED = shared

override WINDRES:=$(PREFIX)$(WINDRES)
override CCFLAGS+= -Wall -Iinclude -I$(DIR_HDR) -D_EASY_GETTEXT_COMPILE_TIME_
override CXXFLAGS+= -Wall -std=c++11
LDFLAGS = -Wall 

ifneq ($(MAKECMDGOALS),debug)
override LDFLAGS+=
override CCFLAGS+=-O3
override CXXFLAGS+=-O3
else
override LDFLAGS+= -g 
override CCFLAGS+= -g 
override CXXFLAGS+= -g 
endif

# Don't edit before this line
# ---------------------------

ifeq (linux,$(findstring linux,$(shell $(CC) -dumpmachine)))
  TGT_WIN=0
  LIB_OS=
else
  ifeq (mingw,$(findstring mingw,$(shell $(CC) -dumpmachine)))
    TGT_WIN=1
    LIB_OS=
  endif
endif

ifeq (,$(TGT_WIN))
define ERR
  
  Error: Unable to define target.
    Manually set  TGT_WIN=1  for Windows target
    or TGT_WIN=0 for Linux target
endef
$(error $(ERR))
endif

ifeq (Windows_NT,$(OS))
  HOST_WINDOWS=1
  RM =del /s /f /q
  COLOR_BLUE =
  COLOR_GREEN=
  COLOR_RED  =
  COLOR_DEF  =
else
  HOST_WINDOWS=0
  RM =rm -rf
  COLOR_BLUE =\033[1;34m
  COLOR_GREEN=\033[1;32m
  COLOR_RED  =\033[31m
  COLOR_DEF  =\033[0m
endif

# LINK_RULE(target,source,linker,flags,dirs)
ifeq ($(HOST_WINDOWS),0)
define LINK_RULE
$(1): $(5) $(2);
	-@echo "$(COLOR_BLUE)Library$(COLOR_GREEN)    $(1)$(COLOR_RED)"
	-@$(RM) $(1)
	-@$(3) -o $(1) $(2) $(4)
	@if [ -f $(1) ]; then echo "$(COLOR_GREEN)           Successfully$(COLOR_DEF)"; else echo "Linking    ERROR$(COLOR_DEF)"; return 1; fi
endef
else
define LINK_RULE
$(1): $(5) $(2);
	-@echo Library    $(1)
	@$(3) -o $(1) $(2) $(4)
	-@echo            Successfully
endef
endif

# LINK_STATIC_RULE(target,source,linker,flags,dirs)
ifeq ($(HOST_WINDOWS),0)
define LINK_STATIC_RULE
$(1): $(5) $(2);
	-@echo "$(COLOR_BLUE)Library$(COLOR_GREEN)    $(1)$(COLOR_RED)"
	-@$(RM) $(1)
	-@$(3) $(4) -o $(1) $(2)
	@if [ -f $(1) ]; then echo "$(COLOR_GREEN)           Successfully$(COLOR_DEF)"; else echo "Linking    ERROR$(COLOR_DEF)"; return 1; fi
endef
else
define LINK_STATIC_RULE
$(1): $(5) $(2);
	-@echo Library    $(1)
	@$(3) $(4) -o $(1) $(2)
	-@echo            Successfully
endef
endif

# COMPILE_RULE(target,source,flags)
ifeq ($(HOST_WINDOWS),0)
define COMPILE_RULE
$(1)/%.o: $(2)/%.c;
	-@echo "$(COLOR_BLUE)Compile$(COLOR_GREEN)    $$@$(COLOR_RED)"
	-@$(RM) $$@
	-@$(CC) $(3) -c $$< -o $$@
	@if [ -f $$@ ]; then return 0; else echo "Compile    ERROR$(COLOR_DEF)"; return 1; fi
endef
else
define COMPILE_RULE
$(1)/%.o: $(2)/%.c;
	-@echo Compile    $$@
	@$(CC) $(3) -c $$< -o $$@
endef
endif

override CCFLAGS+=
override CXXFLAGS+=
override LDFLAGS+=

ifeq (x86_64,$(findstring x86_64,$(shell $(CC) -dumpmachine)))
# Target for 64 bits
TGT_BIT=x64
else
# Target for 32 bits
TGT_BIT=x32
endif

DIR_OBJ_STATIC = $(DIR_OBJ)/$(DIR_STATIC)/$(TGT_BIT)
DIR_OBJ_SHARED = $(DIR_OBJ)/$(DIR_SHARED)/$(TGT_BIT)
DIR_OBJ_EXAMPLE= $(DIR_OBJ)/example/$(TGT_BIT)
DIR_LIB_STATIC = $(DIR_LIB)/$(DIR_STATIC)/$(TGT_BIT)
DIR_LIB_SHARED = $(DIR_LIB)/$(DIR_SHARED)/$(TGT_BIT)

PJ_SRC_WPATH = $(addprefix $(DIR_SRC)/,$(PROJECT_SRC))
PJ_OBJS = $(patsubst %.cpp,%.opp,$(patsubst %.c,%.o,$(PROJECT_SRC)))
ifeq ($(TGT_WIN),1)
#  override PJ_OBJ_WPATH+=$(DIR_OBJ)/resource.o
endif
PJ_OBJ_STATIC_WPATH = $(addprefix $(DIR_OBJ_STATIC)/,$(PJ_OBJS))
PJ_OBJ_SHARED_WPATH = $(addprefix $(DIR_OBJ_SHARED)/,$(PJ_OBJS))
PJ_OBJ_EXAMPLE_WPATH = $(addprefix $(DIR_OBJ_EXAMPLE)/,$(patsubst %.cpp,%.opp,$(patsubst %.c,%.o,$(PROJECT_EXAMPLE))))
PJ_LIB_STATIC_WPATH = $(DIR_LIB_STATIC)/lib$(PROJECT_NAME).a
ifeq ($(TGT_WIN),0)
  PJ_EXE_WPATH = $(DIR_BIN)/$(PROJECT_NAME)
  PJ_EXAMPLE_WPATH = $(DIR_BIN)/example
  PJ_LIB_SHARED_WPATH = $(DIR_LIB_SHARED)/lib$(PROJECT_NAME).so
  CCFLAGS_SHARED  = $(CCFLAGS) -fpic
  CXXFLAGS_SHARED = $(CXXFLAGS) -fpic
  LDFLAGS_SHARED  = $(LDFLAGS) -shared
else
  PJ_EXE_WPATH = $(DIR_BIN)/$(PROJECT_NAME).exe
  PJ_EXAMPLE_WPATH = $(DIR_BIN)/example.exe
  PJ_LIB_SHARED_WPATH = $(DIR_LIB_SHARED)/$(PROJECT_NAME).dll
  CCFLAGS_SHARED  = $(CCFLAGS)
  CXXFLAGS_SHARED = $(CXXFLAGS)
  LDFLAGS_SHARED  = $(LDFLAGS) -shared -Wl,--output-def,$(DIR_LIB_SHARED)/lib$(PROJECT_NAME).def
endif
CCFLAGS_STATIC  = $(CCFLAGS) -DEASY_GETTEXT_STATIC
CXXFLAGS_STATIC = $(CXXFLAGS) -DEASY_GETTEXT_STATIC
LDFLAGS_STATIC  =rcs

CCFLAGS_EXAMPLE  = -Wall -Iinclude -Ihdr
CXXFLAGS_EXAMPLE = -Wall -Iinclude -Ihdr
LDFLAGS_EXAMPLE  = $(LDFLAGS) -L$(DIR_LIB_STATIC) -leasy-gettext


EXCLUDE_EQUALS_PATH=$(sort $(abspath $(dir $(1))))
# For library only
DIRS_SHARED = $(call EXCLUDE_EQUALS_PATH, $(PJ_OBJ_SHARED_WPATH) $(PJ_LIB_SHARED_WPATH))
DIRS_STATIC = $(call EXCLUDE_EQUALS_PATH, $(PJ_OBJ_STATIC_WPATH) $(PJ_LIB_STATIC_WPATH))
DIRS_EXAMPLE= $(call EXCLUDE_EQUALS_PATH, $(PJ_OBJ_EXAMPLE_WPATH) $(PJ_EXAMPLE_WPATH))

DIRS_ALL=$(call EXCLUDE_EQUALS_PATH, $(addsuffix /.dummy,$(DIRS_SHARED) $(DIRS_STATIC) $(DIRS_EXAMPLE)))

