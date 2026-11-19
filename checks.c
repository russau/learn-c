#include "checks.h"
#include "vendor/cjson/cJSON.h"

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
  cJSON *report = cJSON_CreateObject();
  if (report == nullptr) {
    fprintf(stderr, "Could not create report\n");
    return;
  }

  const char *status = launch_ready(summary) ? "GO" : "HOLD";

  if (cJSON_AddNumberToObject(report, "checks",
                             summary->passed + summary->held) == nullptr ||
      cJSON_AddNumberToObject(report, "passed", summary->passed) == nullptr ||
      cJSON_AddNumberToObject(report, "held", summary->held) == nullptr ||
      cJSON_AddStringToObject(report, "launch", status) == nullptr) {
    fprintf(stderr, "Could not populate report\n");
    cJSON_Delete(report);
    return;
  }

  char *json = cJSON_PrintUnformatted(report);
  if (json == nullptr) {
    fprintf(stderr, "Could not serialize report\n");
    cJSON_Delete(report);
    return;
  }

  printf("%s\n", json);

  cJSON_free(json);
  cJSON_Delete(report);
}
