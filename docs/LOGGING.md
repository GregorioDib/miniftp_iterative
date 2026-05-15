# Logging and Daemonization Changes

This project was modified to support daemon-style logging using the Linux syslog service.

## Changes made

- Added a centralized logging module:
  - `logs.c`
  - `logs.h`

- Replaced `printf`, `fprintf(stderr, ...)` and `perror()` calls with:
  - `log_info()`
  - `log_error()`
  - `log_debug()`
  - `log_perror()`

- Logs are now sent to the system logger (`syslog`) instead of stdout/stderr.

## Viewing logs

Example:

```bash
sudo tail -f /var/log/syslog
```

Filter only FTP logs:

```bash
sudo tail -f /var/log/syslog | grep ausftp
```

## Notes

This project does not fully daemonize the process
(using fork(), setsid(), etc.).

The objective of this modification was centralized daemon-compatible logging.
