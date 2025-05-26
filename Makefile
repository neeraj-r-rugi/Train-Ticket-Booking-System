CC = gcc
CFLAGS = -Iinclude
SRC = src/main.c src/process.c src/defines.c
OUT = program.out

all:
	${CC} ${SRC} -o ${OUT} ${CFLAGS}

clean: 
	rm -f $(OUT)
