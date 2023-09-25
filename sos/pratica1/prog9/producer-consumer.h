#ifndef PROD_CONS_H
#define PROD_CONS_H

#define N 100
#define MAILBOX 453

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

typedef struct {
  long type;
  char content[100];
} message;

int setup_mailbox();
void send_message(const int mailbox_id, const message* m);
void receive_message(const int mailbox_id, message* const m);

#endif