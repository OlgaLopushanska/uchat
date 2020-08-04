#include "uchat.h"

char *mx_client(gpointer data, char *u, int n) {
	t_user *s = (t_user*)data;
	int sfd = s->sfd;
	ssize_t msglen;
	ssize_t numbytes;
	int bufsize = 255;
	char *resp = NULL;
	char buf[bufsize];
	//int port = 5002;
	int res = 0;
	
	n = 0;
	 //for (j = 2; j < argc; j++) {
	 	//msglen = mx_strlen(argv[j]);
	 	msglen = mx_strlen(u);
	//while ((msglen = read(STDIN_FILENO), buf, bufsize) > 0) 	
	 	//if (sendto(sfd, u, msglen, 0, (struct sockaddr *)&svaddr, sizeof(struct sockaddr_in)) != msglen)
	 	if ((res =send(sfd, u, msglen, 0)) != msglen)
		 ; //можна send
	 	//ошибка отправки сообщения
	 	numbytes = recv(sfd, buf, bufsize, 0);
	 	//numbytes = read(sfd, buf, bufsize);

		 ; //можна recv
	 	if (numbytes == -1)
		 ; //ошибка передачи сообшения
	return resp;
}

