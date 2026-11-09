CC = clang
CFLAGS = -std=c23 -Wall -Wextra -g -fsanitize=undefined -fno-sanitize-recover=all

preflight: main.c checks.c checks.h
	$(CC) $(CFLAGS) -o preflight main.c checks.c
