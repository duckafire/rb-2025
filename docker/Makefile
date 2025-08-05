PROGRAM_NAME=rb-2025
COMPILER=g++

BIN_DIR=/build/bin
SRC_DIR=./src/

LIB_DEPENDENCES=pthread valkey
LIB_DEPENDENCES:=$(addprefix -l, ${LIB_DEPENDENCES})

FILES_EXT=.cpp
SRC_FILES=main
SRC_FILES:=$(addprefix ${SRC_DIR},   ${SRC_FILES})
SRC_FILES:=$(addsuffix ${FILES_EXT}, ${SRC_FILES})

# call `make FLAGS=-g` to allow
# the GDB debug mode;
FLAGS?=
#FLAGS:=${FLAGS}

all:
	mkdir ${BIN_DIR}
	@${COMPILER} ${SRC_FILES} -o ${BIN_DIR}/${PROGRAM_NAME} ${FLAGS} ${LIB_DEPENDENCES}
