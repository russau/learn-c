#include "checks.h"

#include <stddef.h>

int main(void) {
    const char *results[] = {"PASS", "PASS", "HOLD", "PASS"};
    size_t count = sizeof(results) / sizeof(results[0]);
    CheckSummary summary = {0};
    for (size_t i = 0; i < count; i++) {
        add_check(&summary, results[i]);
    }
    print_report(&summary);
    return 0;
}
