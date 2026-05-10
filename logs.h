#ifndef LOGS_H
#define LOGS_H

void log_init(void);
void log_close(void);

void log_info(const char *fmt, ...);
void log_error(const char *fmt, ...);
void log_debug(const char *fmt, ...);

void log_perror(const char *msg);

#endif
