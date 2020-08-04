#include "uchat.h"

void mx_change_users_list(t_req *req, t_user *s) {
    int i = 0;
    char *temp = NULL;

    mx_list_box(s, 0);
    temp = mx_str_get_sub(&req->req, 0, ':');
    s->n_users = mx_atoi(temp);
    temp = mx_free(temp);
    if (s->n_users) {
        s->users = (char **)malloc(sizeof(char *) * s->n_users);
        for (i = 0; i < s->n_users; i++)
            s->users[i] = mx_str_get_sub(&req->req, 0, ':');
    }
}
