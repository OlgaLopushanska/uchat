#include "uchat.h"

t_user *mx_struct_init(t_user *s) {

    s = (t_user*)malloc(sizeof(t_user));
    s->sfd = -1;
    s->bufsize = 10000;
    s->user = NULL;
    s->pass = NULL;
    s->pass2 = NULL;
    s->email1 = NULL;
    s->sex = NULL;
    s->name = NULL;
    s->surname = NULL;
    s->current = NULL;
    s->snd = NULL;
    s->rcv = NULL;
    s->b_num_rooms = 0;
    s->c_room = -1;
    s->rooms = NULL;
    s->users = NULL;
    s->n_users = 0;
    s->user_row = NULL;
    s->user_lable = NULL;
    s->new_room = NULL;
    s->add_user = NULL;
    s->box_rooms2 = NULL;
    s->box_users2 = NULL;
    s->box_chat1 = NULL;
    s->box_chat2 = NULL;
    s->button = NULL;
    s->c_user = -1;
    s->css_d = "* {\n background-color: RGB(4,9,82);\n }\n";
    s->css_l = "* {\n background-color: RGB(100,166,247);\n }\n";
    s->text = NULL;
    s->n_t = 0;
    s->msg = NULL;
    return s;
}
