#include "uchat.h"

static void press_button(GtkWidget *button, gpointer data);

static void create_buttons(t_user *s);

static void destroy_buttons(t_user *s);

void mx_button_rooms(t_user *s, int par) {
    par ? create_buttons(s) : destroy_buttons(s);
}

static void create_buttons(t_user *s) {
    int i = 0;

    if (s->box_rooms2) {
        s->button = (GtkWidget **)malloc(sizeof(GtkWidget *) * s->b_num_rooms);
        for (i = 0; i < s->b_num_rooms; i++) {
            s->button[i] = gtk_button_new_with_label(s->rooms[i][0]);
            g_signal_connect(s->button[i], "clicked",
            G_CALLBACK(press_button), s);
            gtk_container_add(GTK_CONTAINER(s->box_rooms2), s->button[i]);
        }
    }
}

static void press_button(GtkWidget *button, gpointer data) {
    t_user *s = (t_user*)data;
    int i = 0;
    char *message = NULL;
    char *num = mx_get_current_num();
    t_req *req = NULL;

    for (i = 0; s->button[i] != button && i < s->b_num_rooms; i++)
    ;
    s->c_room = i;
    s->c_user = -1;
    asprintf(&message, "%s", s->rooms[i][1]);
    mx_send_message(num, "4", message, s);
    message = mx_free(message);
    req = mx_recive_message(num, s);
    mx_change_users_list(req, s);
    mx_list_box(s, 1);
    if (s->box_chat2)
        gtk_widget_destroy(s->box_chat2);
    s->box_chat2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    if (s->box_chat1) {
        mx_get_all_history(s);
        gtk_container_add(GTK_CONTAINER(s->box_chat1), s->box_chat2);
    }
    gtk_widget_show_all(s->chat_window);
    req = mx_free_struct_req(req);
}

static void destroy_buttons(t_user *s) {
    int i = 0;

    if (s->button) 
        for (i = 0; i < s->b_num_rooms; i++)
            gtk_widget_destroy(s->button[i]);
    s->button = mx_free(s->button);
    if (s->rooms)
        for (i = 0; i < s->b_num_rooms && s->rooms[i]; i++)
            s->rooms[i] = (char **)mx_free2((void **)s->rooms[i], 2);
    s->rooms = mx_free(s->rooms);
}
