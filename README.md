# MiniFTP - Iterative FTP Server

Educational FTP server written in C using Berkeley sockets.

This repository is based on the MiniFTP iterative server skeleton used in the "Computer Networks II" course at Instituto Politécnico Superior de Rosario.

The objective of the project is to understand:
- socket programming
- FTP command flow
- client/server communication
- signal handling

---

## Current Status

This project currently implements:
- iterative single-client server
- blocking I/O
- FTP control connection
- basic FTP command handling

Implemented FTP commands:
- USER
- PASS
- QUIT
- SYST

Declared but currently incomplete commands:
- TYPE
- PORT
- RETR
- STOR
- NOOP

---

## Logging Update (2026-05-10)

On 2026-05-10, centralized logging support was added using the Linux `syslog` service.

Changes include:
- replacement of `printf`, `fprintf(stderr, ...)` and `perror()` calls
- centralized logging module (`logs.c` / `logs.h`)
- daemon-compatible logging through syslog

Additional details are documented in:

- `LOGGING.md`

---

## Build

Compile the project using:

```bash
make
```

---

## Run

Run the server as root (required for port 21):

```bash
sudo ./miniftp
```

---

## Authentication

User credentials are loaded from:

```text
/etc/ausftp/ftpusers
```

Credential format:

```text
username:password
```

Example:

```text
aus:1234
```

---

## Limitations

This project is educational and intentionally minimal.

Current limitations include:
- no concurrent clients
- incomplete FTP data transfer implementation
- no TLS/FTPS support
- no passive mode support
- not fully daemonized (`fork`, `setsid`, etc. are not implemented)

---

## Technologies Used

- C (GNU11)
- POSIX sockets
- Linux syslog
- Makefile build system

---

## Educational Context

This repository was developed as coursework for:

- Computer Networks II (Redes de las Computadoras II)
- Instituto Politécnico Superior de Rosario
- 2026
