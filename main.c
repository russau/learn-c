#include "checks.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        printf("Usage: preflight [INPUT]\n");
        return EXIT_SUCCESS;
    }
    FILE *input = stdin;
    if (argc >= 2) {
        input = fopen(argv[1], "r");
        if (input == NULL) {
            fprintf(stderr, "Could not open input\n");
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
        fprintf(stderr, "Could not read input\n");
        failed = true;
    }
    if (input != stdin && fclose(input) == EOF) {
        fprintf(stderr, "Could not close input\n");
        failed = true;
    }
    if (failed) {
        return EXIT_FAILURE;
    }
    printf("Latest check: %s\n", latest);
    print_report(&summary);
    if (launch_ready(&summary)) {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
