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
INCLUDE_DIR = $(srcdir)/include
DIR_LIB = $(srcdir)/lib
DIR_OBJ = $(srcdir)/obj


CPP_SUFFIX := cc
OBJ_SUFFIX := o
HEADER_SUFFIX := h

# clear & set suffuxes for implicit rules
.SUFFIXES:
.SUFFIXES: .$(CPP_SUFFIX) .$(OBJ_SUFFIX)



#===============================================================================
# Variables section
#===============================================================================


#-------------------------------------------------------------------------------
# Predefined variables
#-------------------------------------------------------------------------------

## 1) setting the type of the makefile (debug | release)

#-- DO-CHANGE-HERE : comment this line to have a release-Makefile
#debug_mode := 1


## 2) Select project files & paths: VPATH, vpath, sources, objects, headers, ...

#-- DO-CHANGE-HERE
#MAIN_FILE := main.$(CPP_SUFFIX)
MAIN_FILE := 

#project-particular variables


## generic variables

#common/base headers
FN_BASEGRAPH := BaseGraph
FN_DIJKSTRA:= Dijkstra
FN_TYPES:= types

#source files
SOURCES := $(wildcard *.$(CPP_SUFFIX))
DIJKSTRA_SOURCES := $(filter $(FN_DIJKSTRA)%.$(CPP_SUFFIX),$(SOURCES))

#object files
OBJS := $(SOURCES:%.$(CPP_SUFFIX)=$(DIR_OBJ)/%.$(OBJ_SUFFIX))
DIJKSTRA_OBJS:=$(DIJKSTRA_SOURCES:%.$(CPP_SUFFIX)=$(DIR_OBJ)/%.$(OBJ_SUFFIX))


#-- DO-CHANGE-HERE
#lib files
SHLIB_NAME := libpathfinding_shared
STLIB_NAME := libpathfinding_static
SHARED_LIB := $(DIR_OBJ)/$(SHLIB_NAME).so
STATIC_LIB := $(DIR_OBJ)/$(STLIB_NAME).a


#header files & paths # i.e. HEADERS := a.$(HEADER_SUFFIX): b.$(HEADER_SUFFIX)
#-- DO-CHANGE-HERE:  
INCLUDE_DIRECTORIES := $(srcdir)
INCLUDE_DIRECTORIES += $(INCLUDE_DIR)

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



#-------------------------------------------------------------------------------
# Other non-predef variables
#-------------------------------------------------------------------------------

RM=rm -rf
RM.CORES := $(wildcard core.*)
RM.OBJS := $(OBJS) $(DIR_OBJ)
RM.LIBS := $(DIR_LIB)
RM.SAVES :=  $(wildcard *.*~ ) $(wildcard *~)
RM.OTHER_STUFF := $(wildcard *.$(HEADER_SUFFIX).gch)
RM.VALGRIND := vgrind.*.out
#-- DO-CHANGE-HERE
RM.TRASH = $(RM.CORES) \
	   $(RM.OBJS)  \
	   $(RM.LIBS)  \
	   $(RM.SAVES) \
	   $(RM.OTHER_STUFF) \
           $(RM.VALGRIND)


#-------------------------------------------------------------------------------
# (predefined) mkdir commands
#-------------------------------------------------------------------------------

MAKE_DIR_OBJ_GUARD = @mkdir -p $(DIR_OBJ)
MAKE_DIR_LIB_GUARD = @mkdir -p $(DIR_LIB)



#===============================================================================
# public targets section:
#
# default target = all
#===============================================================================

.PHONY: all shlib staticlib
	@echo '$*'


# all: $(OBJS)                      
# 	@echo 'Building target: $@'

all: $(STATIC_LIB)
	@echo 'Building target: $@'


shlib: $(SHARED_LIB)
	@echo 'Building target: $@'


staticlib: $(STATIC_LIB)
	@echo 'Building target: $@'


lib:  $(STATIC_LIB) $(SHARED_LIB)
	@echo 'Building target: $@'


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

COMMON_HEADERS:=  $(FN_BASEGRAPH).$(HEADER_SUFFIX)
COMMON_HEADERS+=  $(FN_TYPES).$(HEADER_SUFFIX)

# objects depending on their own header
$(OBJS): $(DIR_OBJ)/%.$(OBJ_SUFFIX): %.$(HEADER_SUFFIX)
# objects depending on $(FN_DIJKSTRA).$(HEADER_SUFFIX)
$(DIJKSTRA_OBJS): $(DIR_OBJ)/%.$(OBJ_SUFFIX): $(FN_DIJKSTRA).$(HEADER_SUFFIX)
# objects depending on $(COMMON_HEADERS)
$(OBJS): $(DIR_OBJ)/%.$(OBJ_SUFFIX): $(COMMON_HEADERS)



#------------------------------------------------------------------------
# 2) recipe rules
#------------------------------------------------------------------------


#------------------
# a) compilation
#------------------


#CXXFLAGS = -fpic  # -fpic to create a shared library

$(OBJS): $(DIR_OBJ)/%.$(OBJ_SUFFIX): %.$(CPP_SUFFIX)
	@echo ''
	@echo 'Building target: $@'
	$(MAKE_DIR_OBJ_GUARD)
	$(CXX) -c $(all_cxxflags) -fpic $(CPPFLAGS) $<  -o $@ 


#------------------
# b) linking
#------------------

$(SHARED_LIB):$(OBJS)
	@echo ''
	@echo 'Building target: $@'
	$(CXX) -shared $(LDFLAGS) -o $@ $^ $(LDLIBS)
	$(MAKE_DIR_LIB_GUARD)
	mv $@ $(DIR_LIB)



$(STATIC_LIB):$(OBJS)
	@echo ''
	@echo 'Building target: $@'
	ar rv $@ $^
	ranlib $@
	$(MAKE_DIR_LIB_GUARD)
	mv $@ $(DIR_LIB)


# dummy_test: 
# 	@echo 'Building target DIJ_OBS: $(DIJKSTRA_OBJS)'
# 	@echo 'Building target OBJs: $(OBJS)'
# 	@echo 'Building target MODULE_OBJS: $(OBJS)'
# 	@echo 'Building target  EXEC: $(EXEC)'
# 	@echo 'oooodddd'
# 	@echo 'main.$(OBJ_SUFFIX)'
# 	@echo 'exec = $(EXEC)'
# 	@echo 'test_execs = $(TEST_EXECS)'




#===============================================================================
# phony targets
#===============================================================================

.PHONY: clean

clean:
#	clear; $(RM) $(RM.TRASH);
	$(RM) $(RM.TRASH);
        @echo 'Building target: $@'

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

