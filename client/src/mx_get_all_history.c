#include "uchat.h"

static void add_line(t_req *req, t_user *s);

void mx_get_all_history(t_user *s) {
    int n = -1;
    char *num = mx_get_current_num();
    char *temp = NULL;
    t_req *req = NULL;
    int i = 0;

    mx_send_message(num, "10", s->rooms[s->c_room][1], s);
    req = mx_recive_message(num, s);
    n = mx_atoi(req->req);
    req = mx_free_struct_req(req);
    if (s->box_chat2) {
        gtk_widget_destroy(s->box_chat2);
        s->text = (char **)mx_free2((void **)s->text, s->n_t);
        s->msg = mx_free(s->msg);
        s->box_chat2 = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
    }
    s->n_t = 0;
    for (i = 0; i < n; i++) {
        asprintf(&temp, "%s:%d", s->rooms[s->c_room][1], i + 1);
        mx_send_message(num, "11", temp, s);
        temp = mx_free(temp);
        req = mx_recive_message(num, s);
        add_line(req, s);
        req = mx_free_struct_req(req);
    }
    gtk_widget_show_all(s->chat_window);
    num = mx_free(num);
}

static void add_line(t_req *req, t_user *s) {
    char *user = NULL;
    char *text = NULL;
    char *time = NULL;
    char *msg = NULL;

    if (mx_strcmp(req->req, "WRONG") != 0 && req->req) {
        user = mx_str_get_sub(&(req->req), 0, ':');
        time = mx_str_get_sub(&(req->req), 0, ':');
        text = strdup(req->req); 
        asprintf(&msg, "%s %s  %s", user, time, text);
    }
    else 
        msg = mx_strdup("-");
    s->text = (char**)realloc(s->text, sizeof(char *) *(s->n_t + 1));
    s->text[s->n_t] = mx_strdup(msg);
    s->text[s->n_t] = mx_line_resize(s->text[s->n_t], 50);
    msg = mx_free(msg);
    s->msg = (GtkWidget **)realloc(s->msg, sizeof(GtkWidget *) * (s->n_t + 1));
    s->msg[s->n_t] = gtk_button_new_with_label(s->text[s->n_t]);
    gtk_container_add(GTK_CONTAINER(s->box_chat2), s->msg[s->n_t]);
    (s->n_t)++;
    user = mx_free(user);
    time = mx_free(time);
    text = mx_free(text);
    msg = mx_free(msg);
}
