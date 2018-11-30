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
#debug_mode := 1


## 2) Select project files & paths: VPATH, vpath, sources, objects, headers, ...

#project-particular variables


## generic variables

# Note.- variable naming explanation:
# TEST_XXX: only for unitary test files.
# EXEC_XXX: only for the main file of the module/application.
# MODULE_XXX: only for the files that construct the module/application, thus
#             all but test & exec.


#source files
SOURCES := $(wildcard *.$(CPP_SUFFIX))
TEST_SOURCES := $(filter %_test.$(CPP_SUFFIX),$(SOURCES))

#common/base headers
FN_TYPES:= types
FN_FACADE:= path_finding_facade

#object files
OBJS := $(SOURCES:%.$(CPP_SUFFIX)=%.$(OBJ_SUFFIX))
TEST_OBJS := $(TEST_SOURCES:%.$(CPP_SUFFIX)=%.$(OBJ_SUFFIX))



#############################################################################
#pathfinding library
#############################################################################

PATHFINDING_INCLUDE_DIR:=include
PATHFINDING_LIB_DIR:=lib
PATHFINDING_RELPATH:=../..
# PATHFINDING_ABSPATH:=
PATHFINDING_PATH:=$(PATHFINDING_RELPATH)


#-- DO-CHANGE-HERE
#lib headers
PATHFINDING_INCLUDES_PATH:=$(PATHFINDING_PATH)/$(PATHFINDING_INCLUDE_DIR)
#lib files
LIB_PATHFINDING_NAME:=pathfinding_static # STLIB_NAME parameter
LIB_PATHFINDING_PATH:=$(PATHFINDING_PATH)/$(PATHFINDING_LIB_DIR)

#############################################################################



#exec files
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

directed_iface_test.input_options = 
directed_iface_test.run_options = 
directed_iface_test.runtest_output_options = 
directed_iface_test.successtest_output_options = > directed_iface_test.OK
directed_iface_test.difftest_output_options = >directed_iface_test.last_diff

undirected_iface_test.input_options = 
undirected_iface_test.run_options = 
undirected_iface_test.runtest_output_options = 
undirected_iface_test.successtest_output_options = > undirected_iface_test.OK
undirected_iface_test.difftest_output_options = >undirected_iface_test.last_diff


capacity_iface_test.input_options = 
capacity_iface_test.run_options = 
capacity_iface_test.runtest_output_options = 
capacity_iface_test.successtest_output_options = > capacity_iface_test.OK
capacity_iface_test.difftest_output_options = >capacity_iface_test.last_diff


#header files & paths # i.e. HEADERS := a.$(HEADER_SUFFIX): b.$(HEADER_SUFFIX)
#-- DO-CHANGE-HERE:  
INCLUDE_DIRECTORIES := $(srcdir)
#adding shared/static librarie headers
INCLUDE_DIRECTORIES += $(PATHFINDING_INCLUDES_PATH)


# i.e. INCLUDE_DIRECTORIES += $(srcdir)/header
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
RPATH_LINKER_OPTS := 
LDFLAGS = -L$(LIB_PATHFINDING_PATH)
LDFLAGS += $(RPATH_LINKER_OPTS)
LDFLAGS += $(CPP_STD_FLAGS)
# LDLIBS:  library names: (i.e. LDIBS="-lncurses -lm -lsdl")
LDLIBS = -l$(LIB_PATHFINDING_NAME)

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
RM.EXEC :=  $(TEST_EXECS)
RM.LIBS :=
RM.SAVES :=  $(wildcard *.*~ ) $(wildcard *~)
RM.OTHER_STUFF := $(wildcard *.$(HEADER_SUFFIX).gch)
RM.VALGRIND := vgrind.*.out
#-- DO-CHANGE-HERE
RM.OTHER_STUFF += $(TEST_EXECS:%=%.last_diff)
RM.TRASH = $(RM.CORES) \
	   $(RM.EXEC)  \
	   $(RM.LIBS)  \
	   $(RM.SAVES) \
	   $(OBJS) \
	   $(RM.OTHER_STUFF) \
           $(RM.VALGRIND)



#===============================================================================
# public targets: all ...
#
# default target = all
#===============================================================================

.PHONY: all runtest successtest difftest
	@echo '$*'

# .PHONY: test
# #WARNING A phony target SHOULD NOT be a prerequisite of a real target file.


all: test
	@echo 'Building target: $@'

test: $(TEST_EXECS)


#-------------------------------------------------------------------------------
# rules to execute test/main programs
#-------------------------------------------------------------------------------

#!\warning EOLINE is not expanded, so ';' is required to separate
# commands over the shell console.

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

#------------------
# a) compilation
#------------------

# además cada  .o  depende de $(COMMON_HEADERS)
COMMON_HEADERS:=  $(FN_TYPES).$(HEADER_SUFFIX)
COMMON_HEADERS+=  $(FN_FACADE).$(HEADER_SUFFIX)
$(OBJS): %.$(OBJ_SUFFIX): $(COMMON_HEADERS)


#------------------------------------------------------------------------
# 2) recipe rules
#------------------------------------------------------------------------



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

# each test executable depends on its obj file...
$(TEST_EXECS): %: %.$(OBJ_SUFFIX)
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

# .PHONY: memcheck valgrind

# memcheck:
# 	@echo 'Building target: $@'
# 	./scripts/memcheck_to_each_test.sh

# valgrind:
# 	@echo 'Building target: $@'
# 	./scripts/memcheck_to_each_test.sh


#just to check values
# dummy:
# 	@echo 'Building target: $@'
# 	@echo 'VPATH: $(VPATH)'
# 	@echo 'Building target  INC_DIR: $(INCLUDE_DIRECTORIES)'
# 	@echo 'Building target  LDFLAGS: $(LDFLAGS)'
