#pragma once

#include <stdio.h>

typedef struct CheckSummary {
  int passed;
  int held;
} check_summary_t;

bool add_check(check_summary_t *summary, const char *result);
bool launch_ready(const check_summary_t *summary);
bool print_report(const check_summary_t *summary, const char *latest,
                  FILE *output);
