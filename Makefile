CC = gcc
CFLAGS = -c
DATA_FILE = Data.txt

all: hello clean

hello: hashmap.o main.o
	$(CC) hashmap.o main.o -o start

hashmap.o: hashmap.c
	$(CC) $(CFLAGS) hashmap.c -o hashmap.o

main.o: main.c
	$(CC) $(CFLAGS) main.c -o main.o

clean:
	rm -rf *.o hello

check_leaks:
	leaks -atExit -- ./start < $(DATA_FILE)

run:
	./start < $(DATA_FILE)
