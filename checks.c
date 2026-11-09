#include "checks.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool add_check(CheckSummary *summary, const char *result) {
    if (strlen(result) != 4) {
        return false;
    }
    char normalized[5];
    for (size_t i = 0; i < 4; i++) {
        normalized[i] = (char)toupper((unsigned char)result[i]);
    }
    normalized[4] = '\0';

    if (strcmp(normalized, "PASS") == 0) {
        summary->passed++;
    } else if (strcmp(normalized, "HOLD") == 0) {
        summary->held++;
    } else {
        return false;
    }
    return true;
}

bool launch_ready(const CheckSummary *summary) {
    return summary->passed > 0 && summary->held == 0;
}

void print_report(const CheckSummary *summary) {
    const char *status = "HOLD";
    if (launch_ready(summary)) {
        status = "GO";
    }
    int count = summary->passed + summary->held;
    printf("Checks: %d\nPassed: %d\nHeld: %d\nLaunch: %s\n", count, summary->passed,
           summary->held, status);
}
