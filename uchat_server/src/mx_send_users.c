#include "uchat_server.h"

void mx_send_users(t_req *req, t_user *usr) {
    char *message = NULL;

    message = mx_users_get_list(req->req, usr);
    mx_send_message(req->num, "4", message, usr);
    message = mx_free(message);
}
