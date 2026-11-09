#pragma once

typedef struct {
    int passed;
    int held;
} CheckSummary;

bool add_check(CheckSummary *summary, const char *result);
bool launch_ready(const CheckSummary *summary);
void print_report(const CheckSummary *summary);
