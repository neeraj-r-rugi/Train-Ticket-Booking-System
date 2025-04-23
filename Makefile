CC = gcc
CFLAGS = -Iinclude
SRC = src\main.c src\process.c src\defines.c
OUT = program.exe

all:
	${CC} ${SRC} -o ${OUT} ${CFLAGS}

clean: 
	del /Q *.exe