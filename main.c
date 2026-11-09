#include <stdio.h>
#include <string.h>

int main(void) {
    const char *results[] = {"PASS", "PASS", "HOLD", "PASS"};
    size_t count = sizeof(results) / sizeof(results[0]);
    int passed = 0;
    int held = 0;
    for (size_t i = 0; i < count; i++) {
        if (strcmp(results[i], "PASS") == 0) {
            passed++;
        } else {
            held++;
        }
    }
    const char *status = "HOLD";
    if (passed > 0 && held == 0) {
        status = "GO";
    }
    printf("Checks: %zu\nPassed: %d\nHeld: %d\nLaunch: %s\n", count, passed, held,
           status);
    return 0;
}
