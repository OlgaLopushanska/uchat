#include "uchat.h"

void *mx_reciever(void *data) {
    t_user *s = (t_user*)data;
    char *rcv = NULL;
    t_req *req = NULL;
    pthread_t j;

    while (1) {
        pthread_mutex_lock(&(s->Lock));
        if (s->sfd > 0) 
            break;
        pthread_mutex_unlock(&(s->Lock));
        usleep(100000);
    }
    pthread_mutex_unlock(&(s->Lock));
    while (1) {
        rcv = mx_rec_edited(s->sfd);
        if (!rcv) {
            write(2, "uchat:: connection has losted\n", 31);
            s->close = 1;
            g_application_quit(G_APPLICATION(s->app));
            pthread_exit(NULL);
        }
        else
            while (1) {
                pthread_mutex_lock(&(s->Lock));
                if (!(s->rcv)) {
                    s->rcv = mx_strdup(rcv);
                    req = (t_req*)malloc(sizeof(t_req));
                    req->message = mx_strdup(rcv);
                    rcv = mx_free(rcv);
                    pthread_mutex_unlock(&(s->Lock));
                    req = mx_divide_req(req);
                    if (req->type > 1000)
                        pthread_create(&j, NULL, mx_process_request, (void *)s);
                    req = mx_free_struct_req(req);
                    break;
                }
                pthread_mutex_unlock(&(s->Lock));
                usleep(20000);
            }
        usleep(10000);
    }
    return 0;
}
