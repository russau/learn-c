CC = clang
CFLAGS = -std=c23 -Wall -Wextra -g -fsanitize=undefined -fno-sanitize-recover=all

preflight: main.c checks.c checks.h vendor/cjson/cJSON.c vendor/cjson/cJSON.h
	$(CC) $(CFLAGS) -o preflight main.c checks.c vendor/cjson/cJSON.c
