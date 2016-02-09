# Makefile for Client Files

# A few variables

CC=gcc
LIBS=-lmenu -lncursesw -pthread

SRC_DIR=.
EXE_DIR=../exe

EXE = ${EXE_DIR}/Client

${EXE_DIR}/%: %.o
	${CC} -o $@ $< ${LIBS}

%.o: ${SRC_DIR}/%.c ${SRC_DIR}/%.h
	${CC} -o $@ -c $<

all:  ${EXE}


clean:
	@rm -f ${EXE}
