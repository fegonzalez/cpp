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
OBJS := $(SOURCES:%.cpp=%.o)


#-- DO-CHANGE-HERE
# main source file name: i.e. main for main.cpp
EXEC := main


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
#WARNING_FLAGS += -Werror      # all warnings as errors

DEBUG_FLAGS = -g
OPTIM_FLAGS = -O0 # -O0 is the default value
INCLUDE_FLAGS = $(addprefix -I ,$(INCLUDE_DIRECTORIES))

# select C++ version: c++03 / c++11 / ...
#
#CPP_STD_FLAGS = -std=c++14
CPP_STD_FLAGS = -std=c++11
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

RM=rm -f
RM.CORES := $(wildcard core.*)
RM.EXEC := $(EXEC) a.out
RM.SAVES :=  $(wildcard *.*~ ) $(wildcard *~)
RM.OTHER_STUFF := $(wildcard *.h.gch)
#-- DO-CHANGE-HERE
#RM.OTHER_STUFF +=
RM.OTHER_STUFF += $(EXEC:%=%.last_diff)
RM.TRASH = $(RM.CORES) $(RM.EXEC) $(RM.SAVES) $(OBJS) $(RM.OTHER_STUFF)
RM.VALGRIND = bb.out.* cachegrind.out.* callgrind.out.* massif.out.*



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

#------------------
# 1) linking
#------------------

$(EXEC):$(OBJS)
	@echo ''
	@echo 'Building target: $@'
	$(CXX) $(LDFLAGS) -o $@ $^ $(LDLIBS)



#------------------
# 2) compilation
#------------------

#-- DO-CHANGE-HERE
#
# a) Only-dependency rules: to detect changes in headers
#
# (e.g)   main.o: main.h
# (e.g.)  $(OBJS): %.o: $(COMMON_HEADERS)

# b) recipe rules

$(OBJS): %.o: %.cpp
	@echo ''
	@echo 'Building target: $@'
	$(CXX) -c $(all_cxxflags) $(CPPFLAGS) $<  -o $@ 



#===============================================================================
# phony targets
#===============================================================================

.PHONY: clean clean_all

clean:
	clear; $(RM) $(RM.TRASH); ls -l

clean_all:
	clear; $(RM) $(RM.TRASH) $(RM.VALGRIND); ls -l
