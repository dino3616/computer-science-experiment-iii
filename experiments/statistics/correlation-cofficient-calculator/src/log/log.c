#include "log.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool should_print_log(LogLevel_t log_level);

void log_info(const char *format, ...) {
  if (!should_print_log(LOG_LEVEL_INFO)) {
    return;
  }

  va_list args;

  va_start(args, format);
  fprintf(stdout, "\033[32m");
  fprintf(stdout, "Info: ");
  vfprintf(stdout, format, args);
  fprintf(stdout, "\033[0m\n");
  va_end(args);

  return;
}

void log_error(const char *format, ...) {
  if (!should_print_log(LOG_LEVEL_ERROR)) {
    return;
  }

  va_list args;

  va_start(args, format);
  fprintf(stderr, "\033[31m");
  fprintf(stderr, "Error: ");
  vfprintf(stderr, format, args);
  fprintf(stderr, "\033[0m\n");
  va_end(args);

  return;
}

void log_debug(const char *format, ...) {
  if (!should_print_log(LOG_LEVEL_DEBUG)) {
    return;
  }

  va_list args;

  va_start(args, format);
  fprintf(stdout, "\033[33m");
  fprintf(stdout, "Debug: ");
  vfprintf(stdout, format, args);
  fprintf(stdout, "\033[0m\n");
  va_end(args);

  return;
}

bool should_print_log(LogLevel_t log_level) {
  char *log_level_env = getenv("LOG_LEVEL");

  LogLevel_t log_level_env_value;
  if (log_level_env == NULL) {
    log_level_env_value = LOG_LEVEL_ERROR;
  } else {
    if (strcmp(log_level_env, "INFO") == 0) {
      log_level_env_value = LOG_LEVEL_INFO;
    } else if (strcmp(log_level_env, "ERROR") == 0) {
      log_level_env_value = LOG_LEVEL_ERROR;
    } else if (strcmp(log_level_env, "DEBUG") == 0) {
      log_level_env_value = LOG_LEVEL_DEBUG;
    } else {
      log_level_env_value = LOG_LEVEL_ERROR;
    }
  }

  return log_level_env_value >= log_level;
}
