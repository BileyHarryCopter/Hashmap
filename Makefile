CPP = gcc
CPPFLAGS ?= -O2 --std=c18

# c files
SRC = main.c src/hashmap.c
# h files
INCLUDE = -I./include
# data for tests
DATA_FILE = data/data.txt
# including of h files in proccess of compliting
CPPFLAGS += $(INCLUDE)
# obj files
OBJS = $(SRC:.c=.o)
# dependencies files
DEPS = $(SRC:.c=.d)
# build folder


.PHONY: all
all:
	@echo "Compiling..."
	$(CPP) $(CPPFLAGS) $(SRC) -o start

.PHONY: clean
clean:
	@echo "Cleaning all of objects and deps files"
	@rm -rf $(OBJS) $(DEPS)

.PHONY: leaks
leaks:
	@echo "Turn on mode of checking on leaks of memory"
	@leaks -atExit -- ./start < $(DATA_FILE)

.PHONY: run
run:
	@echo "Run the program on the $(DATA_FILE)"
	@./start < $(DATA_FILE)