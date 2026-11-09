#include "checks.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        printf("Usage: preflight [PASS|HOLD ...]\n");
        return EXIT_SUCCESS;
    }
    CheckSummary summary = {0};
    char latest[5] = "NONE";
    if (argc == 1) {
        char line[16];
        while (fgets(line, sizeof(line), stdin) != NULL) {
            size_t length = strlen(line);
            if (length > 0 && line[length - 1] == '\n') {
                line[length - 1] = '\0';
            }
            if (!add_check(&summary, line)) {
                fprintf(stderr, "Invalid check\n");
                return EXIT_FAILURE;
            }
            strcpy(latest, line);
        }
    } else {
        for (int i = 1; i < argc; i++) {
            if (!add_check(&summary, argv[i])) {
                fprintf(stderr, "Invalid check\n");
                return EXIT_FAILURE;
            }
            strcpy(latest, argv[i]);
        }
    }
    printf("Latest check: %s\n", latest);
    print_report(&summary);
    if (launch_ready(&summary)) {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
