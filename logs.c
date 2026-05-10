#include "logs.h"
#include <syslog.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>

void log_init(void) {
    openlog("ausftp", LOG_PID, LOG_DAEMON);
} //Initializes log

void log_close(void) {
    closelog();
} //Closes log

static void vlog_message(int priority, const char *fmt, va_list args) {
    vsyslog(priority, fmt, args);
} //Intern Helper, can recive multiple arguments

void log_info(const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    vlog_message(LOG_INFO, fmt, args);
    va_end(args);
}

void log_error(const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    vlog_message(LOG_ERR, fmt, args);
    va_end(args);
}

void log_debug(const char *fmt, ...) {
    va_list args;

    va_start(args, fmt);
    vlog_message(LOG_DEBUG, fmt, args);
    va_end(args);
}

void log_perror(const char *msg) {
    log_error("%s: %s", msg, strerror(errno));
}
