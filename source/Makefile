CC=gcc
CFLAGS=-Wall -Werror -g

run: build
	./todo

build: main.o list.o
	$(CC) $(CFLAGS) $^ -o todo
	rm main.o list.o

main.o: main.c

list.o: list.c

clean:
	rm -rf main.o list.o todo
