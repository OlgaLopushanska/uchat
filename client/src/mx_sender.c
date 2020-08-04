#include "uchat.h"

void *mx_sender(void *data) {
    t_user *s = (t_user*)data;
    char *snd = NULL;
    int msglen = 0;
    int res = 0;

    while (1) {
        pthread_mutex_lock(&(s->Lock));
        if (s->sfd > 0) 
            break;
        pthread_mutex_unlock(&(s->Lock));
        usleep(100000);
    }
    pthread_mutex_unlock(&(s->Lock));
    while (1) {
        pthread_mutex_lock(&(s->Lock));
        if (s->snd) {
            snd = mx_strdup(s->snd);
            s->snd = mx_free(s->snd);
        }
        pthread_mutex_unlock(&(s->Lock));
        if (snd) {
            msglen = mx_strlen(snd);
            if ((res = send(s->sfd, snd, msglen, 0)) != msglen)
                write(2, "uchat:: error sending message\n", 30);
            if (res == -1)
                exit(1);
            snd = mx_free(snd);
        }
        usleep(10000);
    }
    return 0;
}
