PROJECT_NAME=easy-gettext
PROJECT_SRC =easy-gettext.c

-include inc.mak

all: $(PJ_LIB_SHARED_WPATH) $(PJ_LIB_STATIC_WPATH)
static: $(PJ_LIB_STATIC_WPATH)
shared: $(PJ_LIB_SHARED_WPATH)

$(DIRS_ALL):
ifeq ($(HOST_WINDOWS),0)
	@mkdir -p $@
else
	@mkdir $(subst /,\,$@)
endif

$(call LINK_RULE,$(PJ_LIB_STATIC_WPATH),$(PJ_OBJ_STATIC_WPATH),$(AR),$(LDFLAGS_STATIC),$(DIRS_STATIC))
$(call LINK_RULE,$(PJ_LIB_SHARED_WPATH),$(PJ_OBJ_SHARED_WPATH),$(CC),$(LDFLAGS_SHARED),$(DIRS_SHARED))

$(call COMPILE_RULE,$(DIR_OBJ_STATIC),$(DIR_SRC),$(CCFLAGS_STATIC))
$(call COMPILE_RULE,$(DIR_OBJ_SHARED),$(DIR_SRC),$(CCFLAGS_SHARED))

color:
	-@echo $(COLOR_DEF)

clean:
ifeq ($(HOST_WINDOWS),0)
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
	-@echo         =========== Easy Gettext ===========
	-@echo.
	-@echo Make:
	-@echo   all     Create static and shared library (default)
	-@echo   static  Create a static library
	-@echo   shared  Create a shared library
	-@echo   clean   Delete all generated files
	-@echo   help    Show this help