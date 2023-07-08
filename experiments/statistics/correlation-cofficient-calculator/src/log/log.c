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
  fprintf(stderr, "\033[32m");
  fprintf(stderr, "Info: ");
  vfprintf(stderr, format, args);
  fprintf(stderr, "\033[0m\n");
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
  fprintf(stderr, "\033[33m");
  fprintf(stderr, "Debug: ");
  vfprintf(stderr, format, args);
  fprintf(stderr, "\033[0m\n");
  va_end(args);

  return;
}

bool should_print_log(LogLevel_t log_level) {
  char *log_level_env = getenv("LOG_LEVEL");
  if (log_level_env == NULL) {
    return false;
  }

  LogLevel_t log_level_env_value;
  if (strcmp(log_level_env, "INFO") == 0) {
    log_level_env_value = LOG_LEVEL_INFO;
  } else if (strcmp(log_level_env, "ERROR") == 0) {
    log_level_env_value = LOG_LEVEL_ERROR;
  } else if (strcmp(log_level_env, "DEBUG") == 0) {
    log_level_env_value = LOG_LEVEL_DEBUG;
  } else {
    return false;
  }

  if (log_level_env_value < log_level) {
    return false;
  }

  return true;
}
