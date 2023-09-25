#include "producer-consumer.h"

int setup_mailbox() {
	int msqid = msgget(MAILBOX, 0666 | IPC_CREAT);
	if(msqid <= 0) {
  		perror("erro na criacao de mailbox");
  	}

    return msqid;
}

void send_message(int mailbox_id, const message* m) {
    int flag = msgsnd(mailbox_id, m, strlen(m->content) + 1, 0);
    printf("o resultado eh: %d\n", flag);
}

void receive_message(const int mailbox_id, message* const m) {
    int msgflg = MSG_NOERROR;
    int flag = msgrcv(mailbox_id, m, 100, 0, msgflg);

    if(flag >= 0) {
        printf("o tipo da mensagem eh: %ld\n", m->type);
        printf("o conteudo da mensagem eh: %s\n", m->type != 2 ? m->content : "");
    } else {
        perror("erro na recepcao");
    }
}
