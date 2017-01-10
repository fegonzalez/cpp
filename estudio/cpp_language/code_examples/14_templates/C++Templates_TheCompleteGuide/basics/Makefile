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


# clear & set suffuxes for implicit rules
.SUFFIXES:
.SUFFIXES: .cpp .o


#===============================================================================
# Predefined variables
#===============================================================================

## 1) setting the type of the makefile (debug | release)

#-- DO-CHANGE-HERE : comment this line to have a release-Makefile
debug_mode := 1


## 2) Select project files & paths: VPATH, vpath, sources, objects, headers, ...

#-- DO-CHANGE-HERE
#MAIN_FILE := main.cpp
MAIN_FILE := 

#project-particular variables


## generic variables

# Note.- variable naming explanation:
# TEST_XXX: only for unitary test files.
# EXEC_XXX: only for the main file of the module/application.
# MODULE_XXX: only for the files that construct the module/application, thus
#             all but test & exec.


#source files
SOURCES := $(wildcard *.cpp)
EXEC_SOURCE := $(MAIN_FILE)
TEST_SOURCES := $(filter %test.cpp,$(SOURCES))
MODULE_SOURCES := $(filter-out $(TEST_SOURCES),$(SOURCES))
MODULE_SOURCES := $(filter-out $(EXEC_SOURCE),$(MODULE_SOURCES))

#object files
OBJS := $(SOURCES:%.cpp=%.o)
EXEC_OBJ := $(EXEC_SOURCE:%.cpp=%.o)
TEST_OBJS := $(TEST_SOURCES:%.cpp=%.o)
MODULE_OBJS := $(MODULE_SOURCES:%.cpp=%.o)

#exec files
EXEC := $(EXEC_SOURCE:%.cpp=%)
#-- DO-CHANGE-HERE
EXEC_OPTIONS =
#EXEC_OPTIONS = <./data/add_item 
# case: read test input from file named "/data/add_item"
# make "EXEC_OPTIONS = <./data/add_item" difftest"
#
# TEST_EXECS := $(patsubst %.cpp,%,$(TEST_SOURCES))
TEST_EXECS := $(TEST_SOURCES:%.cpp=%)

#default option values
#
#file expecific option values (MUST be set manually)
#-- DO-CHANGE-HERE

stack1test.input_options = 
stack1test.run_options = 
stack1test.runtest_output_options = 
stack1test.successtest_output_options = > stack1test.OK
stack1test.difftest_output_options = > stack1test.last_diff
#
stack2test.input_options = 
stack2test.run_options = 
stack2test.runtest_output_options = 
stack2test.successtest_output_options = > stack2test.OK
stack2test.difftest_output_options = > stack2test.last_diff
#
stack3test.input_options = 
stack3test.run_options = 
stack3test.runtest_output_options = 
stack3test.successtest_output_options = > stack3test.OK
stack3test.difftest_output_options =  > stack3test.last_diff
#
stack4test.input_options = 
stack4test.run_options = 
stack4test.runtest_output_options = 
stack4test.successtest_output_options = > stack4test.OK
stack4test.difftest_output_options =  > stack4test.last_diff
#
addvaltest.input_options = 
addvaltest.run_options = 
addvaltest.runtest_output_options = 
addvaltest.successtest_output_options = > addvaltest.OK
addvaltest.difftest_output_options =  > addvaltest.last_diff
#
trickybasicstest.input_options = 
trickybasicstest.run_options = 
trickybasicstest.runtest_output_options = 
trickybasicstest.successtest_output_options = > trickybasicstest.OK
trickybasicstest.difftest_output_options =  > trickybasicstest.last_diff
#
asyn_assig_operatortest.input_options = 
asyn_assig_operatortest.run_options = 
asyn_assig_operatortest.runtest_output_options = 
asyn_assig_operatortest.successtest_output_options = > asyn_assig_operatortest.OK
asyn_assig_operatortest.difftest_output_options =  > asyn_assig_operatortest.last_diff
#
stack8test.input_options = 
stack8test.run_options = 
stack8test.runtest_output_options = 
stack8test.successtest_output_options = > stack8test.OK
stack8test.difftest_output_options =  > stack8test.last_diff
#
max5test.input_options = 
max5test.run_options = 
max5test.runtest_output_options = 
max5test.successtest_output_options = > max5test.OK
max5test.difftest_output_options =  > max5test.last_diff
#
max6test.input_options = 
max6test.run_options = 
max6test.runtest_output_options = 
max6test.successtest_output_options = > max6test.OK
max6test.difftest_output_options =  > max6test.last_diff



#header files & paths # i.e. HEADERS := a.h: b.h
#-- DO-CHANGE-HERE:  
INCLUDE_DIRECTORIES := $(srcdir)
# i.e. INCLUDE_DIRECTORIES += $(srcdir)/header
#COMMON_HEADERS=Sales_item.h
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
DEBUG_FLAGS = -g
OPTIM_FLAGS = -O
INCLUDE_FLAGS = $(addprefix -I ,$(INCLUDE_DIRECTORIES))

# select C++ version: c++03 / c++11 / ...
#
CPP_STD_FLAGS = -std=c++14

#CPP_STD_FLAGS += -std=c++11  or via command:
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
RM.EXEC := $(EXEC) a.out $(TEST_EXECS) $(MODULE_SOURCES:%.cpp=%)
RM.SAVES :=  $(wildcard *.*~ ) $(wildcard *~)
RM.OTHER_STUFF := $(wildcard *.h.gch)
#-- DO-CHANGE-HERE
RM.OTHER_STUFF += $(TEST_EXECS:%=%.last_diff)
RM.TRASH = $(RM.CORES) \
	   $(RM.EXEC)  \
	   $(RM.SAVES) \
	   $(OBJS) \
	   $(RM.OTHER_STUFF)



#===============================================================================
# public targets: all ...
#
# default target = all
#===============================================================================

.PHONY: all exec test runexec runtest successtest difftest
	@echo '$*'

all: $(TEST_EXECS) $(EXEC)
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
# (e.g)   main.o: main.h
# (e.g.)  $(OBJS): %.o: $(COMMON_HEADERS)
#
# (e.g.) all the objects that depend on their own header: i.e. dummy.o dummy.h
# 	 e.g.: all the objects but $(EXEC).o have a header.
#        HEADER_OBJS:=$(subst $(EXEC).o,,$(OBJS)) 
#        $(HEADER_OBJS): %.o: %.h


#------------------
# a) compilation
#------------------

$(TEST_OBJS): %test.o: %.hpp


#------------------------------------------------------------------------
# 2) recipe rules
#------------------------------------------------------------------------


#------------------
# a) compilation
#------------------

$(OBJS): %.o: %.cpp
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
$(TEST_EXECS): %: %.o \
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

