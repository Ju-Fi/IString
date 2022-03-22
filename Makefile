NAME = test_istr
CC = gcc
CFLAGS = -g -Wall -Wextra -pedantic -std=c11 -fsanitize=address

SRC = test.c
OBJ = $(notdir $(SRC:.c=.o))

all: clean build

build: $(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(CFLAGS) $(LFLAGS)

obj/%.o: %.c | obj
	$(CC) $< -c $(CFLAGS) -o $@

clean:
	rm -f $(OBJ) $(NAME)

