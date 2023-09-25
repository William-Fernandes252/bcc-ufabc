/*
 * Produtor.
 *
 */

#include "producer-consumer.h"

int main() {
	int msqid, counter = 1;
	message m;

	/* cria estrutura de mensagem */
	msqid = setup_mailbox();

	/* recebe as mensagens vazias */
	while (counter < 100) {
		receive_message(msqid, &m);
		counter += 1;
	}

	while (1) {
		/* preenche estrutura de mensagem */
		m.type = 1;
		sprintf(m.content, "%s %d", "Teste ", counter);

		/* envia */
		send_message(msqid, &m);	

		sleep(1);
	}
}

