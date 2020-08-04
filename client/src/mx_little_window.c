#include "uchat.h"

static void window_room(t_user *s);

static void window_user(t_user *s);

static void press_button(GtkWidget *button, gpointer *data);

void mx_little_window(t_user *s) {
    window_room(s);
    window_user(s);
}

static void press_button(GtkWidget *button, gpointer *data) {
    t_user *s = (t_user*)data;
    char *message = NULL;
    char *num = mx_get_current_num();
    t_req * req = NULL;

    if (button == s->button_new_room) {
        s->new_room = mx_free(s->new_room);
        s->new_room = mx_strdup(gtk_entry_get_text(GTK_ENTRY(s->entry_new_room)));
        if (mx_strlen(s->new_room)) {
            asprintf(&message,"%s:%s", s->user, s->new_room);
            mx_send_message(num, "5", message, s);
            message = mx_free(message);
            req = mx_recive_message(num, s);
            mx_button_rooms_get(req, s, 1);
            req = mx_free_struct_req(req);
            gtk_widget_hide(s->window_new_room);
            gtk_widget_show_all(s->chat_window);
        }
    }
    else if (button == s->button_add_user) {
        s->add_user = mx_free(s->add_user);
        s->add_user= mx_strdup(gtk_entry_get_text(GTK_ENTRY(s->entry_add_user)));
        if (mx_strlen(s->add_user)) {
            asprintf(&message,"%s:%s:%s", s->add_user, s->rooms[s->c_room][1],
                s->rooms[s->c_room][0]);
            mx_send_message(num, "6", message, s);
            message = mx_free(message);
            req = mx_recive_message(num, s);
            if (strcmp(req->req, "Cant find user") == 0) {
                message = mx_strdup("Пользователь с указанным Логином не найден");
                mx_error_dialog(button, data, message);
                message = mx_free(message);
            } 
            else {
                mx_change_users_list(req, s);
                mx_list_box(s, 1); 
                req = mx_free_struct_req(req);
                gtk_widget_hide(s->window_add_user);
                gtk_widget_show_all(s->chat_window);
            }
        }
    }
    num = mx_free(num);
} 

static void window_room(t_user *s) {
    GtkWidget *box;

    s->window_new_room = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(s->window_new_room), "Введите имя комнаты");
    gtk_window_set_position(GTK_WINDOW(s->window_new_room), GTK_WIN_POS_CENTER);
    gtk_window_set_modal(GTK_WINDOW(s->window_new_room), TRUE);
    gtk_window_set_default_size(GTK_WINDOW(s->window_new_room), 200, 200);
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_container_add(GTK_CONTAINER(s->window_new_room), box);
    gtk_container_set_border_width(GTK_CONTAINER(s->window_new_room), 20);
    s->entry_new_room = gtk_entry_new();
    s->button_new_room = gtk_button_new_with_label("Создать");
    g_signal_connect(s->button_new_room, "clicked", G_CALLBACK(press_button), s);
    gtk_container_add(GTK_CONTAINER(box), s->entry_new_room);
    gtk_container_add(GTK_CONTAINER(box), s->button_new_room);
    gtk_widget_hide(s->window_new_room);
}

static void window_user(t_user *s) {
    GtkWidget *box;

    s->window_add_user= gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(s->window_add_user), "Введите имя пользователя");
    gtk_window_set_position(GTK_WINDOW(s->window_add_user), GTK_WIN_POS_CENTER);
    gtk_window_set_modal(GTK_WINDOW(s->window_add_user), TRUE);
    gtk_window_set_default_size(GTK_WINDOW(s->window_add_user), 200, 200);
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_container_add(GTK_CONTAINER(s->window_add_user), box);
    gtk_container_set_border_width(GTK_CONTAINER(s->window_add_user), 20);
    s->entry_add_user = gtk_entry_new();
    s->button_add_user = gtk_button_new_with_label("Добавить");
    g_signal_connect(s->button_add_user, "clicked", G_CALLBACK(press_button), s);
    gtk_container_add(GTK_CONTAINER(box), s->entry_add_user);
    gtk_container_add(GTK_CONTAINER(box), s->button_add_user);
    gtk_widget_hide(s->window_add_user);
}
