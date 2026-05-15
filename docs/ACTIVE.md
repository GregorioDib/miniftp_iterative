# Active Mode (PORT) Implementation

This project was extended to support FTP Active Mode using the `PORT` command.

## Changes made

- Added parsing support for FTP `PORT` arguments:
  - implemented `get_info_from_port()` in `utils.c`

- Added active-mode session state handling:
  - introduced connection mode tracking in `session.h`

- Implemented the `PORT` command handler:
  - parses client IP and port
  - stores remote data endpoint
  - creates a data socket
  - connects to the client data port

- Added debug logging for received `PORT` arguments.

- Added proper FTP response handling:
  - `200 Command okay`
  - `501 Syntax error in parameters`
  - `425 Can't open data connection`

## FTP Active Mode

In active mode:

1. The client sends a `PORT h1,h2,h3,h4,p1,p2` command.
2. The server parses the IP and port.
3. The server initiates the data connection to the client.

Example:

```
PORT 127,0,0,1,172,133
```

Port calculation:

```
172 * 256 + 133 = 44165
```

## Notes

This implementation currently establishes the active data connection
but does not yet implement full file transfer commands (RETR, STOR).

The current goal was infrastructure support for FTP active mode.
