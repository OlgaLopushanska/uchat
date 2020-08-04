#include "uchat.h"

void mx_button_rooms_get(t_req *req, t_user *s, int par) {
    int i = 0;
    char *temp = NULL;

    par = 0;
    if (s->box_chat1)
        mx_button_rooms(s, 0);
    temp = mx_str_get_sub(&req->req, 0, ':');
    s->b_num_rooms = mx_atoi(temp);
    temp = mx_free(temp);
    if (s->b_num_rooms)
        s->rooms = (char ***)malloc(sizeof(char **) * s->b_num_rooms);
    for (i = 0; i < s->b_num_rooms; i++) {
        s->rooms[i] = (char **)malloc(sizeof(char *) * 2);
        s->rooms[i][0] = mx_str_get_sub(&req->req, 0, ':');
        s->rooms[i][1] = mx_str_get_sub(&req->req, 0, ':');
    }
    if (s->box_chat1) {
        mx_button_rooms(s, 1);
        if (s->box_chat2) {
            gtk_widget_destroy(s->box_chat2);
            s->box_chat2 = NULL;
        }
        s->box_chat2 = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
        gtk_container_add(GTK_CONTAINER(s->box_chat1), s->box_chat2);
    }
}
