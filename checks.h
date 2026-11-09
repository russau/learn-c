#pragma once

#include <stdio.h>

typedef struct {
    int passed;
    int held;
} CheckSummary;

bool add_check(CheckSummary *summary, const char *result);
bool launch_ready(const CheckSummary *summary);
bool print_report(const CheckSummary *summary, const char *latest, FILE *output);
