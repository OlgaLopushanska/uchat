#include "uchat.h"

bool mx_add_new_user(t_user *s) {
    t_req *req = NULL;
    char *num = NULL;
    char *request;
    bool res = false;

    asprintf(&request,"%s:%s:%s", s->user, s->pass, s->email1);
    num = mx_get_current_num();
    mx_send_message(num, "1", request, s);
    request = mx_free(request);
    req = mx_recive_message(num, s);
    num = mx_free(num);
    res = mx_strcmp(req->req,"OK New user create") == 0 ? true : false;
    req = mx_free_struct_req(req);
    return res;
}
