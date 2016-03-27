# Makefile for Client Files

# A few variables

CC=gcc
LIBS=-pthread -lmenu -lncurses
EXE_DIR=../exe

${EXE_DIR}/Client: Client.o
	${CC} -o $@ $< ${LIBS}

Client.o: *.c *.h
	${CC} -o $@ -c $<

clean:
	rm -f *.o
