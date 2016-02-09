# Makefile for Server Files

# A few variables

CC=gcc
LIBS=-pthread
EXE_DIR=../exe

${EXE_DIR}/Server: Server.o
	${CC} -o $@ $< ${LIBS}

Server.o: *.c *.h
	${CC} -o $@ -c $<

clean:
	rm -f *.o
