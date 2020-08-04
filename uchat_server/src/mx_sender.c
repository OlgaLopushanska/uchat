#include "uchat_server.h"

void *mx_sender(void *data){
    t_user *usr = (t_user*)data;
    char *snd = NULL;
    int msglen = 0;
    int res = 0;

    while (1) {
        pthread_mutex_lock(&(usr->Lock));
        if(usr->snd){
            snd = mx_strdup(usr->snd);
            usr->snd = mx_free(usr->snd);
        }
        pthread_mutex_unlock(&(usr->Lock));
        if(snd && usr->ext == 0){
            msglen = mx_strlen(snd);
            if ((res = send(usr->cfd, snd, msglen, 0)) != msglen) {
                fprintf(stderr, "\033[31muchat_server:: error sending message - socket \"%d\"\033[0m\n", usr->cfd);//не удалось соедінітся с сокетом
                usr->ext = 1;
            }
            if(res == -1)
                exit(1);
            snd = mx_free(snd);
        }
        usleep(50000);

    }
    return 0;
}
