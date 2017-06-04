PROJECT_NAME=easy-gettext
PROJECT_SRC =easy-gettext.c

-include inc.mak

all: $(PJ_LIB_SHARED_WPATH) $(PJ_LIB_STATIC_WPATH)

static $(PJ_LIB_STATIC_WPATH): $(DIRS) $(DIRS_STATIC) $(PJ_OBJ_STATIC_WPATH)
ifeq ($(WIN),0)
	-@echo "$(COLOR_BLUE)Library$(COLOR_GREEN)    $(PJ_LIB_STATIC_WPATH)$(COLOR_RED)"
	-@$(RM) $(PJ_LIB_STATIC_WPATH)
	-@$(AR) $(LDFLAGS_STATIC) $(PJ_LIB_STATIC_WPATH) $(PJ_OBJ_STATIC_WPATH)
	@if [ -f $(EX1_OUT_WPATH) ]; then echo "\033[1;32m           Successfully\033[0m"; else echo "Linking    ERROR\033[0m"; return 1; fi;
else
	-@echo Library    $(PJ_LIB_STATIC_WPATH)
	@$(AR) $(LDFLAGS_STATIC) $(PJ_LIB_STATIC_WPATH) $(PJ_OBJ_STATIC_WPATH)
	-@echo            Successfully
endif

shared $(PJ_LIB_SHARED_WPATH): $(DIRS) $(DIRS_SHARED) $(PJ_OBJ_SHARED_WPATH)
ifeq ($(WIN),0)
	-@echo "$(COLOR_BLUE)Library$(COLOR_GREEN)    $(PJ_LIB_SHARED_WPATH)$(COLOR_RED)"
	-@$(RM) $(PJ_LIB_SHARED_WPATH)
	-@$(CC) $(LDFLAGS_SHARED) -o $(PJ_LIB_SHARED_WPATH) $(PJ_OBJ_SHARED_WPATH)
	@if [ -f $(EX1_OUT_WPATH) ]; then echo "\033[1;32m           Successfully\033[0m"; else echo "Linking    ERROR\033[0m"; return 1; fi;
else
	-@echo Library    $(PJ_LIB_SHARED_WPATH)
	@$(CC) $(LDFLAGS_SHARED) -o $(PJ_LIB_SHARED_WPATH) $(PJ_OBJ_SHARED_WPATH)
	-@echo            Successfully
endif

$(DIRS) $(DIRS_SHARED) $(DIRS_STATIC):
ifeq ($(WIN),0)
	-@mkdir $@
else
	-@mkdir $(subst /,\\,$@)
endif

$(DIR_OBJ_STATIC)/%.o: $(DIR_SRC)/%.c
ifeq ($(WIN),0)
	-@echo "$(COLOR_BLUE)Compile$(COLOR_GREEN)    $@$(COLOR_RED)"
	-@$(RM) $@
	-@$(CC) $(CCFLAGS_STATIC) -c $< -o $@
	@if [ -f $@ ]; then return 0; else echo "Compile    ERROR\033[0m"; return 1; fi;
else
	-@echo Compile    $@
	@$(CC) $(CCFLAGS_STATIC) -c $< -o $@
endif

$(DIR_OBJ_SHARED)/%.o: $(DIR_SRC)/%.c
ifeq ($(WIN),0)
	-@echo "$(COLOR_BLUE)Compile$(COLOR_GREEN)    $@$(COLOR_RED)"
	-@$(RM) $@
	-@$(CC) $(CCFLAGS_SHARED) -c $< -o $@
	@if [ -f $@ ]; then return 0; else echo "Compile    ERROR\033[0m"; return 1; fi;
else
	-@echo Compile    $@
	@$(CC) $(CCFLAGS_SHARED) -c $< -o $@
endif

color:
	-@echo $(COLOR_DEF)

clean:
ifeq ($(WIN),0)
	-@echo "$(COLOR_BLUE)Cleaning project$(COLOR_RED)"
	-$(RM) $(DIR_LIB)
	-$(RM) $(DIR_OBJ)
	-@echo "$(COLOR_DEF)"
else
	-@echo Cleaning project
	-@$(RM) $(subst /,\\,$(DIR_OBJ))
	-@$(RM) $(subst /,\\,$(DIR_LIB))
	-@rmdir /s /q $(DIR_OBJ)
	-@rmdir /s /q $(DIR_LIB)
endif

help:
	@echo         =========== Easy Gettext ===========
	@echo.
	@echo Make:
	@echo   all     Create static and shared library (default)
	@echo   static  Create a static library
	@echo   shared  Create a shared library
	@echo   clean   Delete all generated files
	@echo   help    Show this help