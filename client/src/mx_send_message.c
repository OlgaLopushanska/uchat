#include "uchat.h"

void mx_send_message(char* num_msg, char* type, char *msg, t_user *s) {
    while (1) {
        pthread_mutex_lock(&(s->Lock));
        if (!(s->snd)) {
            s->snd = mx_strdup(num_msg);
            s->snd = mx_strjoin(s->snd, ":");
            s->snd = mx_strjoin(s->snd, type);
            s->snd = mx_strjoin(s->snd, ":");
            s->snd = mx_strjoin(s->snd, msg);
            pthread_mutex_unlock(&(s->Lock));
            break;
        }
        pthread_mutex_unlock(&(s->Lock));
    }
}
