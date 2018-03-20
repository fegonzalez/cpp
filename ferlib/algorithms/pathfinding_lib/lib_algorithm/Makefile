#===============================================================================
# 
# Basic GENERIC (*) Makefile for C++ valid for any program (static
# pattern & implicit rules used)
#
# Default configuration = using DEBUG options
#
# (*) Do changes (if necessary) only after this label:  DO-CHANGE-HERE
#
#===============================================================================
#
# c++11 support
#
# make "CPP_STD_FLAGS = -std=c++11" all
#
# c++14 support
#
# make "CPP_STD_FLAGS = -std=c++14" all
#
# Optional : Parallel Execution: make -j4 ...
#===============================================================================
#
# INFO Automatic Variables meaning
#
# $@  The file name of the target.
#
# $<  The name of the first prerequisite.
#
# $^ (S+)  The names of all the prerequisites (preserve duplicate pres.)
#
# $?  The names of all the prerequisites that are newer than the target.
#
# WARNING limited scope
# It’s very important that you recognize the limited scope in which automatic
# variable values are available: they only have values within the recipe.
#===============================================================================



#===============================================================================
# Makefile Begins
#===============================================================================

#===============================================================================
# Setting Makefile Conventions
#===============================================================================

SHELL := /bin/sh

# set source dir
srcdir := .

CPP_SUFFIX := cc
OBJ_SUFFIX := o
HEADER_SUFFIX := h

# clear & set suffuxes for implicit rules
.SUFFIXES:
.SUFFIXES: .$(CPP_SUFFIX) .$(OBJ_SUFFIX)


#===============================================================================
# Predefined variables
#===============================================================================

## 1) setting the type of the makefile (debug | release)

#-- DO-CHANGE-HERE : comment this line to have a release-Makefile
debug_mode := 1


## 2) Select project files & paths: VPATH, vpath, sources, objects, headers, ...

#-- DO-CHANGE-HERE
#MAIN_FILE := main.$(CPP_SUFFIX)
MAIN_FILE := 

#project-particular variables


## generic variables

# Note.- variable naming explanation:
# TEST_XXX: only for unitary test files.
# EXEC_XXX: only for the main file of the module/application.
# MODULE_XXX: only for the files that construct the module/application, thus
#             all but test & exec.


#source files
SOURCES := $(wildcard *.$(CPP_SUFFIX))
EXEC_SOURCE := $(MAIN_FILE)
TEST_SOURCES := $(filter %_test.$(CPP_SUFFIX),$(SOURCES))
MODULE_SOURCES := $(filter-out $(TEST_SOURCES),$(SOURCES))
MODULE_SOURCES := $(filter-out $(EXEC_SOURCE),$(MODULE_SOURCES))

#common/base headers
FN_BASEGRAPH := BaseGraph
FN_DIJKSTRA:= Dijkstra

#object files
OBJS := $(SOURCES:%.$(CPP_SUFFIX)=%.$(OBJ_SUFFIX))
EXEC_OBJ := $(EXEC_SOURCE:%.$(CPP_SUFFIX)=%.$(OBJ_SUFFIX))
TEST_OBJS := $(TEST_SOURCES:%.$(CPP_SUFFIX)=%.$(OBJ_SUFFIX))
MODULE_OBJS := $(MODULE_SOURCES:%.$(CPP_SUFFIX)=%.$(OBJ_SUFFIX))

#exec files
EXEC := $(EXEC_SOURCE:%.$(CPP_SUFFIX)=%)
#-- DO-CHANGE-HERE
EXEC_OPTIONS =
#EXEC_OPTIONS = <./data/add_item 
# case: read test input from file named "/data/add_item"
# make "EXEC_OPTIONS = <./data/add_item" difftest"
#
# TEST_EXECS := $(patsubst %.$(CPP_SUFFIX),%,$(TEST_SOURCES))
TEST_EXECS := $(TEST_SOURCES:%.$(CPP_SUFFIX)=%)

#default option values
#
#file expecific option values (MUST be set manually)
#-- DO-CHANGE-HERE

directed_dijkstra_test.input_options = 
directed_dijkstra_test.run_options = 
directed_dijkstra_test.runtest_output_options = 
directed_dijkstra_test.successtest_output_options = > directed_dijkstra_test.OK
directed_dijkstra_test.difftest_output_options = >directed_dijkstra_test.last_diff


undirected_dijkstra_test.input_options = 
undirected_dijkstra_test.run_options = 
undirected_dijkstra_test.runtest_output_options = 
undirected_dijkstra_test.successtest_output_options = > undirected_dijkstra_test.OK
undirected_dijkstra_test.difftest_output_options = >undirected_dijkstra_test.last_diff


#header files & paths # i.e. HEADERS := a.$(HEADER_SUFFIX): b.$(HEADER_SUFFIX)
#-- DO-CHANGE-HERE:  
INCLUDE_DIRECTORIES := $(srcdir)
# i.e. INCLUDE_DIRECTORIES += $(srcdir)/header
#COMMON_HEADERS=Sales_item.$(HEADER_SUFFIX)
#
# Best Practice: allow 'make' to find files in directories other than 'srcdir'
#
# make Search order:
#
#   i)   local directory
#   ii)  vpath "directories" 
#   iii) VPATH directories.
#
#-- DO-CHANGE-HERE
VPATH := $(INCLUDE_DIRECTORIES)
#vpath := 


#test execution files
# 1) foreach  unit_test en $(TEST_EXECS)
# crear una lista RUN.TEST_TARGETS para runtest: run.unit_test
# crear una lista SUCCESS.TEST_TARGETS para successtest: success.unit_test
# crear una lista DIFF.TEST_TARGETS para difftest: diff.unit_test
RUN.TEST_TARGETS := $(TEST_EXECS:%=run.%)
SUCCESS.TEST_TARGETS := $(TEST_EXECS:%=success.%)
DIFF.TEST_TARGETS := $(TEST_EXECS:%=diff.%)


## 3) Compilation & Linkage


WARNING_FLAGS = -Wall -Wextra # enable additional warnings 
WARNING_FLAGS += -Werror      # all warnings as errors
DEBUG_FLAGS = -ggdb -g -O0 -DTRACE_OUT -DTRACE_SEQ  #-DTRACE_NOTIFY  -DTRACE_SYNCHRO -DTRACE_TIME
OPTIM_FLAGS = -O2
INCLUDE_FLAGS = $(addprefix -I ,$(INCLUDE_DIRECTORIES))

# select C++ version: c++03 / c++11 / ...
#
CPP_STD_FLAGS =            
CPP_STD_FLAGS += -std=c++11
ifeq ($(CPP_STD_FLAGS), -std=c++11)
WARNING_FLAGS += -Wc++11-compat
WARNING_FLAGS += -Wno-missing-field-initializers
else ifeq ($(CPP_STD_FLAGS), -std=gnu++11)
WARNING_FLAGS += -Wc++11-compat
WARNING_FLAGS += -Wno-missing-field-initializers
else ifeq ($(CPP_STD_FLAGS), -std=c++14)
# #WARNING_FLAGS += -Wc++14-compat
WARNING_FLAGS += -Wno-missing-field-initializers
else ifeq ($(CPP_STD_FLAGS), -std=gnu++14)
# #WARNING_FLAGS += -Wc++14-compat
WARNING_FLAGS += -Wno-missing-field-initializers
endif


# Compiling C++ programs
CXX := g++
# preprocessor flags: CPPFLAGS
CPPFLAGS =
# compilation flags: optional flags (CXXFLAGS) + required flags
CXXFLAGS = 
required_cxxflags += $(INCLUDE_FLAGS)
required_cxxflags += $(CPP_STD_FLAGS)

# Linking #-- DO-CHANGE-HERE
#
# LDFLAGS: flags (i.e -g), and library paths (i.e. -L path-lib)
LDFLAGS =	
LDFLAGS += $(CPP_STD_FLAGS)
# LDLIBS:  library names: (i.e. LDIBS="-lncurses -lm -lsdl")
LDLIBS =

ifdef debug_mode
CXXFLAGS += $(WARNING_FLAGS)
CXXFLAGS += $(DEBUG_FLAGS)
LDFLAGS += $(DEBUG_FLAGS)
else
CXXFLAGS += $(WARNING_FLAGS)
CXXFLAGS += $(OPTIM_FLAGS)
LDFLAGS += $(OPTIM_FLAGS)
endif

all_cxxflags = $(required_cxxflags) $(CXXFLAGS)



#===============================================================================
# Other non-predef variables
#===============================================================================

# RM=rm -f
RM.CORES := $(wildcard core.*)
RM.EXEC := $(EXEC) a.out $(TEST_EXECS) $(MODULE_SOURCES:%.$(CPP_SUFFIX)=%)
RM.SAVES :=  $(wildcard *.*~ ) $(wildcard *~)
RM.OTHER_STUFF := $(wildcard *.$(HEADER_SUFFIX).gch)
RM.VALGRIND := vgrind.*.out
#-- DO-CHANGE-HERE
RM.OTHER_STUFF += $(TEST_EXECS:%=%.last_diff)
RM.TRASH = $(RM.CORES) \
	   $(RM.EXEC)  \
	   $(RM.SAVES) \
	   $(OBJS) \
	   $(RM.OTHER_STUFF) \
           $(RM.VALGRIND)



#===============================================================================
# public targets: all ...
#
# default target = all
#===============================================================================

.PHONY: all exec test runexec runtest successtest difftest
	@echo '$*'

# all: $(TEST_EXECS) $(EXEC)  # tests are in ./test
all: $(OBJS)
	@echo 'Building target: $@'


exec: $(EXEC)
	@echo 'Building target: $@'

test: $(TEST_EXECS)


#-------------------------------------------------------------------------------
# rules to execute test/main programs
#-------------------------------------------------------------------------------

#!\warning EOLINE is not expanded, so ';' is required to separate
# commands over the shell console.

RUNEXEC_COMMAND = ./$(exec_unit) $(EXEC_OPTIONS)


RUNTEST_COMMAND = \
		./$(test_unit) \
		$($(test_unit).input_options) \
		$($(test_unit).run_options) \
		$($(test_unit).runtest_output_options) ;

SUCCESSTEST_COMMAND = \
		./$(test_unit) \
		$($(test_unit).input_options) \
		$($(test_unit).run_options) \
		$($(test_unit).successtest_output_options) ;

DIFFTEST_COMMAND = \
		./$(test_unit) \
		$($(test_unit).input_options) \
		$($(test_unit).run_options) \
		$($(test_unit).difftest_output_options) ; \
		echo '\ndiff result on: $(test_unit)' ; \
		diff $(test_unit).last_diff $(test_unit).OK ;


#------------------
# main-program execution
#------------------

runexec:exec
	@echo 'Building target: $@'
	$(foreach exec_unit,$(EXEC),$(RUNEXEC_COMMAND))
	@echo 'Finished building: $@'


#------------------
# test execution - all in a row
#------------------

runtest:test
	@echo 'Building target: $@'
	$(foreach test_unit,$(TEST_EXECS),$(RUNTEST_COMMAND))
	@echo ''
	@echo 'Finished building: $@'


successtest:test
	@echo 'Building target: $@'
	$(foreach test_unit,$(TEST_EXECS),$(SUCCESSTEST_COMMAND))
	@echo ''
	@echo 'Finished building: $@'


difftest:test
	@echo 'Building target: $@'
	$(foreach test_unit,$(TEST_EXECS),$(DIFFTEST_COMMAND))
	@echo ''
	@echo 'Finished building: $@'


#------------------
# test execution - one by one
#------------------

$(RUN.TEST_TARGETS): run.%: %
	@echo ''
	@echo 'Building target: $@'
	./$< $($(<).input_options) \
		$($(<).run_options) \
		$($(<).runtest_output_options)

$(SUCCESS.TEST_TARGETS): success.%: %
	@echo ''
	@echo 'Building target: $@'
	./$< $($(<).input_options) \
		$($(<).run_options) \
		$($(<).successtest_output_options)

$(DIFF.TEST_TARGETS): diff.%: %
	@echo ''
	@echo 'Building target: $@'
	./$< $($(<).input_options) \
		$($(<).run_options) \
		$($(<).difftest_output_options) ; \
	     diff $<.last_diff $<.OK


#===============================================================================
# Compilation & linking via implicit (pattern) rules
#===============================================================================


#------------------------------------------------------------------------
# 1) Only-dependency rules: to detect changes in headers
#------------------------------------------------------------------------
#
#-- DO-CHANGE-HERE
#
# (e.g)   main.$(OBJ_SUFFIX): main.$(HEADER_SUFFIX)
# (e.g.)  $(OBJS): %.$(OBJ_SUFFIX): $(COMMON_HEADERS)
#
# (e.g.) all the objects that depend on their own header: i.e. dummy.$(OBJ_SUFFIX) dummy.$(HEADER_SUFFIX)
# 	 e.g.: all the objects but $(EXEC).$(OBJ_SUFFIX) have a header.
#        HEADER_OBJS:=$(subst $(EXEC).$(OBJ_SUFFIX),,$(OBJS)) 
#        $(HEADER_OBJS): %.$(OBJ_SUFFIX): %.$(HEADER_SUFFIX)

#------------------
# a) compilation
#------------------


# cada  .o (que no es un test) depende de su .h
$(MODULE_OBJS): %.$(OBJ_SUFFIX): %.$(HEADER_SUFFIX)

COMMON_HEADERS:=  $(FN_BASEGRAPH).$(HEADER_SUFFIX)
$(OBJS): %.$(OBJ_SUFFIX): $(COMMON_HEADERS)

DIJKSTRA_SOURCES := $(filter $(FN_DIJKSTRA)%.$(CPP_SUFFIX),$(SOURCES))
DIJKSTRA_OBJS := $(DIJKSTRA_SOURCES:%.$(CPP_SUFFIX)=%.$(OBJ_SUFFIX))
$(DIJKSTRA_OBJS): %.$(OBJ_SUFFIX): $(FN_DIJKSTRA).$(HEADER_SUFFIX)



# main.$(OBJ_SUFFIX): $(FN_DIJKSTRA).$(HEADER_SUFFIX)
# $(TEST_OBJS): %_test.$(OBJ_SUFFIX): %.hpp


#------------------------------------------------------------------------
# 2) recipe rules
#------------------------------------------------------------------------


# dummy: 
# 	@echo 'Building target DIJ_OBS: $(DIJKSTRA_OBJS)'
# 	@echo 'Building target OBJs: $(OBJS)'
# 	@echo 'Building target MODULE_OBJS: $(MODULE_OBJS)'
# 	@echo 'Building target  EXEC: $(EXEC)'
# 	@echo 'oooodddd'
# 	@echo 'main.$(OBJ_SUFFIX)'
# 	@echo 'exec = $(EXEC)'
# 	@echo 'test_execs = $(TEST_EXECS)'




#------------------
# a) compilation
#------------------

$(OBJS): %.$(OBJ_SUFFIX): %.$(CPP_SUFFIX)
	@echo ''
	@echo 'Building target: $@'
	$(CXX) -c $(all_cxxflags) $(CPPFLAGS) $<  -o $@ 


#------------------
# b) linking
#------------------


$(EXEC):$(EXEC_OBJ) $(MODULE_OBJS)
	@echo ''
	@echo 'Building target: $@'
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)


# each test executable depends on its obj file...
# ... and in any of the module objects.
$(TEST_EXECS): %: %.$(OBJ_SUFFIX) \
              $(MODULE_OBJS)  
	@echo ''
	@echo 'Building target: $@'
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)



#===============================================================================
# phony targets
#===============================================================================

.PHONY: clean

clean:
	clear; $(RM) $(RM.TRASH); ls -l


#===============================================================================
# valgrind targets
#===============================================================================

.PHONY: memcheck valgrind

memcheck:
	@echo 'Building target: $@'
	./scripts/memcheck_to_each_test.sh

valgrind:
	@echo 'Building target: $@'
	./scripts/memcheck_to_each_test.sh