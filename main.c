#include "checks.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        printf("Usage: preflight PASS|HOLD ...\n");
        return EXIT_SUCCESS;
    }
    CheckSummary summary = {0};
    const char *latest = "NONE";
    for (int i = 1; i < argc; i++) {
        if (!add_check(&summary, argv[i])) {
            printf("Invalid check\n");
            return EXIT_FAILURE;
        }
        latest = argv[i];
    }
    printf("Latest check: %s\n", latest);
    print_report(&summary);
    if (launch_ready(&summary)) {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
