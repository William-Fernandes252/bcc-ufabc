/*
 * Consumidor.
 *
 */

#include "producer-consumer.h"

int main() {
	int msqid;
	message m;

	/* cria estrutura de mensagem */
	msqid = setup_mailbox();
	for (int i = 0; i < N; i++) {
		m.type = 2; /* mensagem vazia */
		/* envia mensagem vazia */
		send_message(msqid, &m);
	}

	while (1) {
		/* recebe mensagem */
		receive_message(msqid, &m);
	}
}

