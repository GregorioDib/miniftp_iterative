#pragma once

# include "config.h"
#include <netinet/in.h> // sockaddr_in

typedef enum {
  MODE_NONE,
  MODE_ACTIVE,
  MODE_PASSIVE
} transfer_mode_t;

typedef struct {
  int control_sock;                // Control connection
  int data_sock;                   // Data connection
  struct sockaddr_in data_addr;    // For PORT command
  transfer_mode_t mode;            // Connection mode Active/Passive
  char current_user[USERNAME_MAX]; // Session username
  uint8_t logged_in;               // 0 = false, 1 = true
} ftp_session_t;

// Global pointer to current session (set by each child process)
extern ftp_session_t *current_sess;

ftp_session_t *session_get(void);
void session_init(int control_fd);
void session_cleanup(void);
