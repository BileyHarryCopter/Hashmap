CC=gcc
CFLAGS=-c

all: hello clean

hello: hashmap.o main.o
	$(CC) hashmap.o main.o -o start

hashmap.o: hashmap.c
	$(CC) $(CFLAGS) hashmap.c

main.o: main.c
	$(CC) $(CFLAGS) main.c

clean:
	rm -rf *.o hello
