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

- iterative FTP server architecture
- blocking I/O model
- FTP control connection handling
- basic FTP command parsing and dispatching
- USER / PASS authentication
- centralized syslog-based logging
- signal handling (SIGINT / SIGTERM)
- partial FTP Active Mode (`PORT`) support
- active data socket connection establishment

Currently missing or incomplete:

- passive mode (`PASV`)
- file transfer commands (`RETR`, `STOR`)
- directory listing commands (`LIST`, `NLST`)
- concurrent clients
- full daemonization

Implemented FTP commands:
- USER
- PASS
- QUIT
- SYST
- PORT (partially)

Declared but currently incomplete commands:
- TYPE
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

- `docs/LOGGING.md`

---

## Active Mode Update (2026-05-15)

On 2026-05-15, FTP Active Mode support was partially implemented through the `PORT` command.

Changes include:

- parsing FTP `PORT` command arguments
- active-mode session state handling
- client data socket connection support
- centralized debug logging for `PORT` requests
- FTP response handling for active connections

Additional details are documented in:

- `docs/ACTIVE.md`

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
- PORT command not fully implemented yet

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
