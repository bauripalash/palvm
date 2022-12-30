SRC= main.c
CC_FLAGS = -Wall -Wextra -g -std=c11
CC = clang

all:
	$(CC) $(SRC) $(CC_FLAGS) -o pvm

