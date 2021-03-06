#===============================================================================
# 
# Basic GENERIC (*) Makefile for C++ valid for any program (implicit rules used)
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

SOURCES := $(wildcard *.cpp)
# TEST_SOURCES := $(filter %_test.cpp,$(SOURCES)) # only %_test.cpp files
OBJS := $(SOURCES:%.cpp=%.o)


#-- DO-CHANGE-HERE
#
# execution command (runtest, difftest): ./$(EXEC) $(EXEC_OPTIONS)
# EXEC: main source file name: i.e. main for main.cpp
# EXEC_OPTIONS: execution options
#
# case: default execution
# futfill with the test source name
#
#\error "Text file busy" msg. error after executing make is due to this:
# EXEC := main # write some comment here cause the "Text file busy ..." error
# ... instead of this:
# EXEC := main
EXEC := main
EXEC_OPTIONS =
#
# case: read test input from file
# EXEC_OPTIONS = <file_path/file_name
# i.e. make "EXEC_OPTIONS = <./data/add_item" runtest


#-- DO-CHANGE-HERE:  header files & paths
# i.e. HEADERS := a.h: b.h 
INCLUDE_DIRECTORIES := $(srcdir)
# i.e. INCLUDE_DIRECTORIES += $(srcdir)/header


# allow 'make' to find files in directories other than 'srcdir'
#
# make Search order:
#
#   i)   local directory
#   ii)  vpath "directories" 
#   iii) VPATH directories.

#-- DO-CHANGE-HERE
VPATH := $(INCLUDE_DIRECTORIES)
#vpath := 


## 3) Compilation & Linkage

WARNING_FLAGS = -Wall -Wextra # enable additional warnings 
WARNING_FLAGS += -Werror      # all warnings as errors
DEBUG_FLAGS = -g
OPTIM_FLAGS = -O
INCLUDE_FLAGS = $(addprefix -I ,$(INCLUDE_DIRECTORIES))

# select C++ version: c++03 / c++11 / ...
#
CPP_STD_FLAGS =            
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
RM.EXEC := $(EXEC) a.out
RM.SAVES :=  $(wildcard *.*~ ) $(wildcard *~)
RM.OTHER_STUFF := $(wildcard *.h.gch)
#-- DO-CHANGE-HERE
#RM.OTHER_STUFF +=
RM.OTHER_STUFF += $(EXEC:%=%.last_diff)
RM.TRASH = $(RM.CORES) $(RM.EXEC) $(RM.SAVES) $(OBJS) $(RM.OTHER_STUFF)



#===============================================================================
# public targets: all ...
#
# default target = all
#===============================================================================

.PHONY: all

all: $(EXEC)


runtest:all
	@echo 'Building target: $@'
	./$(EXEC)
	@echo ''
	@echo 'Finished building: $@'

 
successtest:all
	@echo 'Building target: $@'
	./$(EXEC) > $(EXEC).OK
	@echo ''
	@echo 'Finished building: $@'


difftest:all
	@echo 'Building target: $@'
	./$(EXEC) > $(EXEC).last_diff
	diff -s $(EXEC).last_diff $(EXEC).OK
	@echo ''
	@echo 'Finished building: $@'




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

$(EXEC):$(OBJS)
	@echo ''
	@echo 'Building target: $@'
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)




#===============================================================================
# phony targets
#===============================================================================

.PHONY: clean

clean:
	clear; $(RM) $(RM.TRASH); ls -l
