#include "uchat.h"
#include <ctype.h>

void chat_server(int port);

 int main(int argc, char *argv[]) {
	 //int port = 5002;

	 chat_server(mx_atoi(argv[1]));
 }
void chat_server(int port) {
	struct sockaddr_in svaddr, claddr;
	int sfd, j, cfd;
	ssize_t numbytes;
	socklen_t len;
	int bufsize = 0;
	char buf[bufsize];
	ssize_t inet_addsrtlen = 0;
	char claddrStr[inet_addsrtlen];
	//inet6_addrstrlen;
	//int port = 5002;
	int backlog = 5;
	
	sfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sfd == -1)
	;
		//ошибкасоздания сокета
	mx_memset(&svaddr, 0, sizeof(struct sockaddr_in));
	svaddr.sin_family = AF_INET;
	svaddr.sin_addr.s_addr = htons(INADDR_ANY);
	svaddr.sin_port = htons(port); //можна
	if (bind(sfd, (struct sockaddr *) &svaddr, sizeof(struct sockaddr_in)) == -1)
	;//не удалось привязать сокет к адресу
	if (listen(sfd, backlog) == -1)
	;//не удалось соедінітся с сокетом
	for (; ; ) {
		len = sizeof(struct sockaddr_in);
		cfd = accept(sfd, NULL, NULL); //создаем новий  сокет слушающий
		if (cfd == -1)
		;//ошібка созданія нового сокета*/
		numbytes = recv(sfd, buf, bufsize, 0);
		while(numbytes > 0) {
		if (numbytes == -1) 
		; //ошибка
		if (inet_ntop(AF_INET, &claddr.sin_addr, claddrStr, inet_addsrtlen) == NULL)
			printf("Couldn't convert client address to string\n"); //заменить
		//ошибка конвертирования адреса клиента
		else
			printf("Server received %ld bytes from (%s, %u)\n", (long) numbytes, claddrStr, ntohs(claddr.sin_port));// cервер получил numbytes от claddrStr, ntohs(claddr.sin6_port)
		for (j = 0; j < numbytes; j++)
			buf[j] = toupper((unsigned char) buf[j]);
		if (send(sfd, buf, numbytes, 0) != numbytes)
		;
			//ошибка отправки сообшения
		}
	}
}
