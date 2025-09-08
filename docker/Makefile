LIBS_DEP?=
SRC_FILES?=

COMPILER=g++
PROGRAM_NAME=run
BIN_DIR=/build/bin
SRC_DIR=/build/src
INC_DIR=/build/include

LIBS_DEP_FORMATED:=$(foreach libfile, ${LIBS_DEP}, -l${libfile})

SRC_FILES_FORMATED:=$(foreach file, ${SRC_FILES}, ${SRC_DIR}/${file})
SRC_FILES_FORMATED:=$(addsuffix .cpp, ${SRC_FILES_FORMATED})

all:
	mkdir ${BIN_DIR}
	${COMPILER} ${SRC_FILES_FORMATED} -o ${BIN_DIR}/${PROGRAM_NAME} ${LIBS_DEP_FORMATED} -I ${INC_DIR}
