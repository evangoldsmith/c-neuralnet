C_SOURCES = $(wildcard net/*.c *.c)
HEADERS = $(wildcard net/*.h *.h)
OBJ = ${C_SOURCES:.c=.o}

MAIN = main
CC = /usr/bin/gcc
LINKER = /usr/bin/ld

run: ${MAIN}
	./${MAIN}

main: ${OBJ}
	${CC} ${CFLAGS} $^ -o $@ -lm

# Generic rules
%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@ -lm

clean:
	rm net/*.o *.o ${MAIN}
