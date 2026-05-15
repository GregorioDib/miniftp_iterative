// handlers.c

#include "responses.h"
#include "pi.h"
#include "dtp.h"
#include "logs.h"
#include "session.h"
#include "utils.h"
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void handle_USER(const char *args) {
  ftp_session_t *sess = session_get();

  if (!args || strlen(args) == 0) {
    safe_dprintf(sess->control_sock, MSG_501); // Syntax error in parameters
    return;
  }

  strncpy(sess->current_user, args, sizeof(sess->current_user) - 1);
  sess->current_user[sizeof(sess->current_user) - 1] = '\0';
  safe_dprintf(sess->control_sock, MSG_331); // Username okay, need password
}

void handle_PASS(const char *args) {

  ftp_session_t *sess = session_get();

  if (sess->current_user[0] == '\0') {
    safe_dprintf(sess->control_sock, MSG_503); // Bad sequence of commands
    return;
  }

  if (!args || strlen(args) == 0) {
    safe_dprintf(sess->control_sock, MSG_501); // Syntax error in parameters
    return;
  }

  if (check_credentials(sess->current_user, (char *)args) == 0) {
    sess->logged_in = 1;
    safe_dprintf(sess->control_sock, MSG_230); // User logged in
  } else {
    safe_dprintf(sess->control_sock, MSG_530); // Not logged in
    sess->current_user[0] = '\0'; // Reset user on failed login
    sess->logged_in = 0;
  }
}

void handle_QUIT(const char *args) {
  ftp_session_t *sess = session_get();
  (void)args; // unused

  safe_dprintf(sess->control_sock, MSG_221); // 221 Goodbye.
  sess->current_user[0] = '\0'; // Close session
  close_fd(sess->control_sock, "client socket"); // Close socket
  sess->control_sock = -1;
}

void handle_SYST(const char *args) {
  ftp_session_t *sess = session_get();
  (void)args; // unused

  safe_dprintf(sess->control_sock, MSG_215); // 215 <system type>
}

void handle_TYPE(const char *args) {
  ftp_session_t *sess = session_get();
  (void)args;
  (void)sess;

  // Placeholder
}

void handle_PORT(const char *args) {
  ftp_session_t *sess = session_get();

  if (!args || strlen(args) == 0) {            // PORT requires:
    safe_dprintf(sess->control_sock, MSG_501); // h1,h2,h3,h4,p1,p2
    return;
  }

  log_debug("PORT command received with args: %s", args);

  char ip[INET_ADDRSTRLEN];
  uint16_t port;

  if (get_info_from_port(args, ip, &port) < 0) { // Parse client IP and port from PORT command
    safe_dprintf(sess->control_sock, MSG_501);
    return;
  }

  memset(&sess->data_addr, 0, sizeof(sess->data_addr)); // Configure client address for active mode connection
  sess->data_addr.sin_family = AF_INET;
  sess->data_addr.sin_port = htons(port);

  if (inet_pton(AF_INET, ip, &sess->data_addr.sin_addr) <= 0) {
    safe_dprintf(sess->control_sock, MSG_501);
    return;
  }

  sess->data_sock = socket(AF_INET, SOCK_STREAM, 0); // Create data socket
  if (sess->data_sock < 0) {
    log_perror("PORT socket creation failed");
    safe_dprintf(sess->control_sock, MSG_425);
    return;
  }

  if (connect(sess->data_sock,                      // Active mode:
              (struct sockaddr *)&sess->data_addr,  // server connects back to client data port
              sizeof(sess->data_addr)) < 0) {

    log_perror("PORT connect failed");

    close_fd(sess->data_sock, "data socket");
    sess->data_sock = -1;

    safe_dprintf(sess->control_sock, MSG_425);
    return;
  }

  log_info("Active data connection established to %s:%u", ip, port);

  safe_dprintf(sess->control_sock, MSG_200);
}

void handle_RETR(const char *args) {
  ftp_session_t *sess = session_get();
  (void)args;
  (void)sess;

  // Placeholder
}

void handle_STOR(const char *args) {
  ftp_session_t *sess = session_get();
  (void)args;
  (void)sess;

  // Placeholder
}

void handle_NOOP(const char *args) {
  ftp_session_t *sess = session_get();
  (void)args;
  (void)sess;

  // Placeholder
}
