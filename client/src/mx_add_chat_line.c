#include "uchat.h"

void mx_add_chat_line(t_req *req, t_user *s) {
    char *user = NULL;
    char *id_room = NULL;
    char *text = NULL;
    char *time = NULL;
    char *msg = NULL;
    int i = 0;

    user = mx_str_get_sub(&(req->req), 0, ':');
    id_room = mx_str_get_sub(&(req->req), 0, ':');
    time = mx_str_get_sub(&(req->req), 0, ':');
    text = mx_strdup(req->req);
    for (i = 0; i < s->b_num_rooms && mx_strcmp(id_room, s->rooms[i][1]); i++)
        ;
    if ( i == s->c_room) {
        asprintf(&msg, "%s %s  %s", user, time, text);
        (s->n_t)++;
        s->text = (char**)realloc(s->text, sizeof(char *) * (s->n_t));
        s->text[s->n_t - 1] = mx_strdup(msg);
        s->text[s->n_t - 1] = mx_line_resize(s->text[s->n_t - 1], 50);
        s->msg = (GtkWidget **)realloc(s->msg, sizeof(GtkWidget *) * (s->n_t));
        s->msg[s->n_t - 1] = gtk_button_new_with_label(s->text[s->n_t - 1]);
        gtk_container_add(GTK_CONTAINER(s->box_chat2), s->msg[s->n_t - 1]);
        gtk_widget_show_all(s->chat_window);
    }
    user = mx_free(user);
    id_room = mx_free(id_room);
    time = mx_free(time);
    text = mx_free(text);
    msg = mx_free(msg);
}
