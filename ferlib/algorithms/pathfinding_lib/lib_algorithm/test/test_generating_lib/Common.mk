#===============================================================================

# INFO Makefile defining the common parameters for every Makefile that
#      uses the pathfinding library (see #-- pathfinding-library
#      section). Add this parameters to the Common.mk file of your
#      project.


#############################################################################
#-- pathfinding-library
#############################################################################

#Dirs

#REL_DIR_PATHFINDING_ALGORITHM: to be defined in the local Makefile that
#uses the algortihm, then expanded at  DIR_PATHFINDING_ALGORITHM
DIR_PATHFINDING_ALGORITHM = $(abspath $(REL_DIR_PATHFINDING_ALGORITHM))
PATHFINDING_INCLUDE_DIR:=include
PATHFINDING_LIB_DIR:=lib
PATHFINDING_LIB_NAME:=pathfinding_static
PATHFINDING_LIB_COMPLETENAME=lib$(PATHFINDING_LIB_NAME).a

MAKE_PATHFINDING_ALGORITHM_GUARD = @$(MAKE) -C $(DIR_PATHFINDING_ALGORITHM)
MAKE_CLEAN_PATHFINDING_ALGORITHM_GUARD = \
	@$(MAKE) -C $(DIR_PATHFINDING_ALGORITHM) clean

#############################################################################
