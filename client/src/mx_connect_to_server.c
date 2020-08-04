#include "uchat.h"

void *mx_connect_to_server(void *data) {
    t_user *s = (t_user *)data;
    struct sockaddr_in svaddr;
    int sfd = -1;
    struct hostent *serv = NULL;

    while (s->sfd <= 0) {
        sfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sfd < 0)
            fprintf(stderr, "uchat:: ошибка создания сокета\n");
        serv = gethostbyname(s->argv[1]);    
        if (!serv)
            fprintf(stderr, "uchat error:: no host\n");
        mx_memset(&svaddr, 0, sizeof(struct sockaddr_in));
        svaddr.sin_family = AF_INET;
        svaddr.sin_port = htons(mx_atoi(s->argv[2]));
        if (inet_pton(AF_INET, s->argv[1], &svaddr.sin_addr) <= 0)
        ;
        if (connect(sfd, (struct sockaddr *)&svaddr,
            sizeof(struct sockaddr_in)) == -1) {
            fprintf(stderr,
            "uchat:: error connecting to server. Please waith I`m trying\n");
            sfd = -1;
        }
        else {
            printf("%s ", "uchat:: \033[0;32mConnected to server\033[0;32m");
            printf("%s : %s\n", s->argv[1], s->argv[2]);
        }
        sleep(1);
        s->sfd = sfd;
    }
    return NULL;
}
