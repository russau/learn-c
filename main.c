#include "checks.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        printf("Usage: preflight [INPUT [OUTPUT]]\n");
        return EXIT_SUCCESS;
    }
    FILE *input = stdin;
    if (argc >= 2) {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            perror(argv[1]);
            return EXIT_FAILURE;
        }
    }

    CheckSummary summary = {0};
    char latest[5] = "NONE";
    bool failed = false;
    char line[16];
    while (fgets(line, sizeof(line), input) != NULL) {
        size_t length = strlen(line);
        if (length > 0 && line[length - 1] == '\n') {
            line[length - 1] = '\0';
        }
        if (!add_check(&summary, line)) {
            fprintf(stderr, "Invalid check\n");
            failed = true;
            break;
        }
        strcpy(latest, line);
    }
    if (ferror(input)) {
        perror("Reading input");
        failed = true;
    }
    if (input != stdin && fclose(input) == EOF) {
        perror("Closing input");
        failed = true;
    }
    if (failed) {
        return EXIT_FAILURE;
    }
    FILE *output = stdout;
    if (argc >= 3) {
        output = fopen(argv[2], "w");
        if (output == NULL) {
            perror(argv[2]);
            return EXIT_FAILURE;
        }
    }
    if (!print_report(&summary, latest, output)) {
        perror("Writing report");
        failed = true;
    }
    if (output != stdout && fclose(output) == EOF) {
        perror("Closing output");
        failed = true;
    }
    if (failed) {
        return EXIT_FAILURE;
    }
    if (launch_ready(&summary)) {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
