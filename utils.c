#define _POSIX_C_SOURCE 200809L
#include "server.h"
#include "logs.h"
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>

void close_fd(int fd, const char *label) {

  if (close(fd) < 0) {
    log_error("Error closing %s", label);
  }
}

ssize_t safe_dprintf(int fd, const char *format, ...) {
  va_list args;
  va_start(args, format);
  ssize_t ret = vdprintf(fd, format, args);
  va_end(args);

  if (ret < 0) {
    log_perror("dprintf error");
  }
  return ret;
}

int get_info_from_port(const char *args, char *ip, uint16_t *port) {
  int h1, h2, h3, h4;
  int p1, p2;

  if (sscanf(args, "%d,%d,%d,%d,%d,%d",
      &h1, &h2, &h3, &h4, &p1, &p2) != 6) {
    return -1;
  }

  snprintf(ip, INET_ADDRSTRLEN, "%d.%d.%d.%d",
      h1, h2, h3, h4);

  *port = p1 * 256 + p2;

  return 0;
}
