#include "uchat.h"

t_req *mx_free_struct_req(t_req *req) {
    if (!req)
        return req;
    req->message = mx_free(req->message);
    req->num = mx_free(req->num);
    req->req = mx_free(req->req);
    req = mx_free(req);
    return req;
}
