#include "uchat.h"

t_req *mx_recive_message(char *num, t_user *s) {
    t_req *req = (t_req*)malloc(sizeof(t_req));

    while (1) {
        pthread_mutex_lock(&(s->Lock));
        if (s->rcv){
            if (mx_get_substr_index(s->rcv, num) >= 0) {
                req->message = mx_strdup(s->rcv);
                s->rcv = mx_free(s->rcv);
                pthread_mutex_unlock(&(s->Lock));
                break;
            }
        }
        pthread_mutex_unlock(&(s->Lock));
        usleep(10000);
    }
    req = mx_divide_req(req);
    return req;
}
