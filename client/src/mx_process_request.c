#include "uchat.h"

static void process_request2(t_req *req, t_user *s);

void *mx_process_request(void *data) {
    t_user *s = (t_user*)data;
    t_req *req = (t_req*)malloc(sizeof(t_req));

    while (1) {
        pthread_mutex_lock(&(s->Lock));
        if (s->rcv) {
            req->message = mx_strdup(s->rcv);
            s->rcv = mx_free(s->rcv);
            pthread_mutex_unlock(&(s->Lock));
            break;
        }
        pthread_mutex_unlock(&(s->Lock));
        usleep(10000);
    }
    req = mx_divide_req(req);
    process_request2(req, s);
    pthread_exit(NULL);
}

static void process_request2(t_req *req, t_user *s) {
    if (req->type == 1001)
        mx_add_chat_line(req, s);
    if (req->type == 1002)
        mx_redraw_room(req, s);
    req = mx_free_struct_req(req);
}
