#include "checks.h"

#include <stdio.h>
#include <string.h>

bool add_check(check_summary_t *summary, const char *result) {
  if (strcmp(result, "PASS") == 0) {
    summary->passed++;
  } else if (strcmp(result, "HOLD") == 0) {
    summary->held++;
  } else {
    return false;
  }
  return true;
}

bool launch_ready(const check_summary_t *summary) {
  return summary->passed > 0 && summary->held == 0;
}

void print_report(const check_summary_t *summary) {
  const char *status = "HOLD";
  if (launch_ready(summary)) {
    status = "GO";
  }
  int count = summary->passed + summary->held;
  printf("Checks: %d\nPassed: %d\nHeld: %d\nLaunch: %s\n", count,
         summary->passed, summary->held, status);
}
