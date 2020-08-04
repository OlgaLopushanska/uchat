#include "uchat.h"

t_req *mx_divide_req(t_req *req) {
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
