#include "uchat_server.h"

char *mx_recive_message(char *num, t_user *usr) {
    char *res = NULL;

    while (1) {
        pthread_mutex_lock(&(usr->Lock));
        if(usr->rcv){
            if(mx_get_substr_index(usr->rcv, num) >= 0) {
                res = mx_strdup(usr->rcv);
                usr->rcv = mx_free(usr->rcv);
                pthread_mutex_unlock(&(usr->Lock));
                break;
            }
        }
        pthread_mutex_unlock(&(usr->Lock));
        usleep(10000);
    }
    return res;

}