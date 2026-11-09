#include "checks.h"

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *results[] = {"PASS", "pass", "Hold", "Pass"};
    size_t count = sizeof(results) / sizeof(results[0]);
    CheckSummary summary = {0};
    for (size_t i = 0; i < count; i++) {
        add_check(&summary, results[i]);
    }
    printf("Latest check: %s\n", results[count - 1]);
    print_report(&summary);
    if (launch_ready(&summary)) {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}
