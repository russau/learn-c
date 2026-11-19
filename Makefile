CC = clang
CFLAGS = -std=c23 -Wall -Wextra -g

preflight: main.c checks.c checks.h
	$(CC) $(CFLAGS) -o preflight main.c checks.c
