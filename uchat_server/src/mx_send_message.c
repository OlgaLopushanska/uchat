#include "uchat_server.h"

void mx_send_message(char* num_msg, char* type, char *msg, t_user *usr) {

    while (1) {
        pthread_mutex_lock(&(usr->Lock));
        if(!(usr->snd)){
            usr->snd = mx_strdup(num_msg);
            usr->snd = mx_strjoin(usr->snd, ":");
            usr->snd = mx_strjoin(usr->snd, type);
            usr->snd = mx_strjoin(usr->snd, ":");
            usr->snd = mx_strjoin(usr->snd, msg);
            pthread_mutex_unlock(&(usr->Lock));
            break;
        }
        pthread_mutex_unlock(&(usr->Lock));

    }
}