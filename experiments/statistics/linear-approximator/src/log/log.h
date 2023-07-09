#ifndef LOG_LOG_H
#define LOG_LOG_H

typedef enum LogLevel {
  LOG_LEVEL_INFO,
  LOG_LEVEL_ERROR,
  LOG_LEVEL_DEBUG,
} LogLevel_t;

extern void log_info(const char *format, ...);
extern void log_error(const char *format, ...);
extern void log_debug(const char *format, ...);

#endif
