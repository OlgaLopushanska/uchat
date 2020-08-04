#include "uchat_server.h"

static t_req *divide_req(t_req *req);

static t_req *free_struct_req(t_req *req);

void *mx_process_request(void *data) {
    t_user *usr = (t_user*)data;
    t_req *req = (t_req*)malloc(sizeof(t_req));

    pthread_mutex_lock(&(usr->Lock));
    req->message = mx_strdup(usr->rcv);
    usr->rcv = mx_free(usr->rcv);
    pthread_mutex_unlock(&(usr->Lock));
    req = divide_req(req);

    mx_process_request2(req, usr);
    req = free_struct_req(req);
    return 0;
}

static t_req *divide_req(t_req *req) {
    char *temp = NULL;
    char *r = NULL;

    r = mx_strdup(req->message);
    req->num = mx_str_get_sub(&(r), 0, ':');
    temp = mx_str_get_sub(&(r), 0, ':');
    req->type = mx_atoi(temp);
    temp = mx_free(temp);
    req->req = mx_strdup (r);
    r = mx_free(r);
    return req;
}

static t_req *free_struct_req(t_req *req) {
    req->message = mx_free(req->message);
    req->num = mx_free(req->num);
    req->req = mx_free(req->req);
    req = mx_free(req);
    return req;
}
