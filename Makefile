.POSIX:

include config.mk

#---------------------------------------------

all: optimise

#-----------------------------------------------

optimise:
	$(COMPILER) ./$(NAME_PROGRAM)/source.$(LANGUAGE) $(C_FLAGS) $(C_LIBS) -o ./$(NAME_PROGRAM)/binary

build:
	$(COMPILER) ./$(NAME_PROGRAM)/source.$(LANGUAGE) $(C_FLAGS) $(C_EXTRA) $(C_LIBS) -o ./$(NAME_PROGRAM)/binary

.PHONY: all build optimise
