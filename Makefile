PROJECT_NAME=easy-gettext
PROJECT_SRC =easy-gettext.c easy-plural.c easy-plural-list.c
PROJECT_EXAMPLE=example.c

-include inc.mak

.PHONY: shared static example
all: shared static
static: $(PJ_LIB_STATIC_WPATH)
shared: $(PJ_LIB_SHARED_WPATH)
example: static $(PJ_EXAMPLE_WPATH)

$(DIRS_ALL):
ifeq ($(HOST_WINDOWS),0)
	@mkdir -p $@
else
	@mkdir $(subst /,\,$@)
endif

$(call LINK_STATIC_RULE,$(PJ_LIB_STATIC_WPATH),$(PJ_OBJ_STATIC_WPATH),$(AR),$(LDFLAGS_STATIC),$(DIRS_STATIC))
$(call LINK_RULE,$(PJ_LIB_SHARED_WPATH),$(PJ_OBJ_SHARED_WPATH),$(CC),$(LDFLAGS_SHARED),$(DIRS_SHARED))
$(call LINK_RULE,$(PJ_EXAMPLE_WPATH),$(PJ_OBJ_EXAMPLE_WPATH),$(CC),$(LDFLAGS_EXAMPLE),$(DIRS_EXAMPLE))

$(call COMPILE_RULE,$(DIR_OBJ_STATIC),$(DIR_SRC),$(CCFLAGS_STATIC))
$(call COMPILE_RULE,$(DIR_OBJ_SHARED),$(DIR_SRC),$(CCFLAGS_SHARED))
$(call COMPILE_RULE,$(DIR_OBJ_EXAMPLE),$(DIR_SRC),$(CCFLAGS_EXAMPLE))

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