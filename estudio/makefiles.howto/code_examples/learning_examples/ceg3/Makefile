# To run this makefile on your files, type:
#
# make 


RM=rm -f
CORE_DUMPS=core.*
TRASH= $(OBJS) $(EXEC).last_diff $(EXEC) $(EXEC).o $(CORE_DUMPS) a.out *.*~ *~ 

.RECIPEPREFIX := :

define exec_special_vars 
@ echo MAKEFILE_LIST : ${MAKEFILE_LIST}
@ echo .DEFAULT_GOAL : ${.DEFAULT_GOAL}
@ echo MAKE_RESTARTS : ${MAKE_RESTARTS}
@ echo .RECIPEPREFIX : ${.RECIPEPREFIX}
@ echo .FEATURES : ${.FEATURES}
@ echo .INCLUDE_DIRS : ${.INCLUDE_DIRS}
@ echo MAKE_TERMOUT : ${MAKE_TERMOUT}
@ echo MAKE_TERMERR : ${MAKE_TERMERR}
endef
#@ echo .VARIABLES : ${.VARIABLES) 

.PHONY: clean all

all: 
: @echo $(exec_special_vars)

clean:
: clear; $(RM) $(TRASH); ls -l

