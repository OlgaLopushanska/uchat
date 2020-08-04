#include "uchat.h"

static void exit_chat(GtkWidget *button, gpointer *data) {
	t_user *s = (t_user*)data;
    
    button = NULL;
    gtk_widget_destroy(s->a_window);
    gtk_widget_destroy(s->chat_window);
    s->close = 1;
    close(s->sfd);
    g_application_quit(G_APPLICATION(s->app));
}

void mx_chat_main(GtkApplication* app, gpointer data) {
    t_user *s = (t_user*)data;
    GtkWidget *button_out;
    GtkWidget *mesage;
    GtkWidget *delet_r;
    GtkWidget *delet_u;
    GtkWidget *box;
    GtkWidget *box2;
    GtkWidget *box3;
    GtkWidget *button_box1;
    GtkWidget *button_box2;
    GtkWidget *button_box3;
    GtkWidget *box31;
    GtkWidget *box32;

    app = NULL;
    s->chat_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(s->chat_window), "ЧАТ");
    gtk_window_set_position(GTK_WINDOW(s->chat_window), GTK_WIN_POS_CENTER);
    gtk_window_set_modal(GTK_WINDOW(s->chat_window), TRUE);
    gtk_window_set_default_size(GTK_WINDOW(s->chat_window),850, 1000);
    box2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    s->box_rooms = mx_create_scroll(s->box_rooms, 150, 500, s);
    s->box_users = mx_create_scroll(s->box_users, 150, 500, s);
    box2 = mx_create_scroll(box2, 500, 500, s);
    gtk_scrolled_window_set_placement (GTK_SCROLLED_WINDOW(box2),
        GTK_CORNER_BOTTOM_RIGHT);
    s->box_chat1 = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
    gtk_container_add(GTK_CONTAINER(box2), s->box_chat1);
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    box3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    s->box4 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 20);
    button_box1 = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
    gtk_box_set_spacing(GTK_BOX(button_box1), 10);
    button_box2 = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
    gtk_box_set_spacing(GTK_BOX(button_box2), 10);
    button_box3 = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
    gtk_box_set_spacing(GTK_BOX(button_box3), 10);
    box31 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 1);
    box32 = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 1);
    mx_add_style(s->chat_window, 1, s);
    gtk_container_add(GTK_CONTAINER(s->chat_window), box);
	gtk_container_set_border_width(GTK_CONTAINER(s->chat_window), 20);
    if (s->current == NULL)
    ;
    else
       s->chat_label1 = gtk_label_new(s->current);
    s->chat_entry = gtk_entry_new();
    s->but_c_new_chat = gtk_button_new_with_label("Добавить комнату");
    delet_r = gtk_button_new_with_label("Удалить комнату");
    mesage = gtk_button_new_with_label("Отправить");
    button_out = gtk_button_new_with_label("Выйти");
    s->but_c_add_user = gtk_button_new_with_label("Добавить пользователя");
    delet_u = gtk_button_new_with_label("Удалить пользователя");
    g_signal_connect(s->but_c_new_chat, "clicked", G_CALLBACK(mx_add_room), s);
    g_signal_connect(s->but_c_add_user, "clicked", G_CALLBACK(mx_add_room), s);
    g_signal_connect(delet_u, "clicked", G_CALLBACK(mx_del_user_from_room), s);
    g_signal_connect(delet_r, "clicked", G_CALLBACK(mx_del_room), s);
    g_signal_connect(mesage, "clicked", G_CALLBACK(mx_send_text_line), s);
    g_signal_connect(button_out, "clicked", G_CALLBACK(exit_chat), s);
    gtk_container_add(GTK_CONTAINER(box31), s->chat_entry);
    gtk_container_add(GTK_CONTAINER(button_box1), s->but_c_new_chat);
    gtk_container_add(GTK_CONTAINER(button_box1), delet_r);
    gtk_container_add(GTK_CONTAINER(button_box2), mesage);
    gtk_container_add(GTK_CONTAINER(button_box2), button_out);
    gtk_container_add(GTK_CONTAINER(button_box3), s->but_c_add_user);
    gtk_container_add(GTK_CONTAINER(button_box3), delet_u);
    gtk_container_add(GTK_CONTAINER(box32), button_box1);
    gtk_box_pack_start(GTK_BOX(box32), button_box2, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(box32), button_box3);
    gtk_container_add(GTK_CONTAINER(box3), box31);
    gtk_container_add(GTK_CONTAINER(box3), box32);
    s->box_rooms2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    mx_button_rooms(s, 1);
    gtk_container_add(GTK_CONTAINER(s->box_rooms), s->box_rooms2);
    gtk_container_add(GTK_CONTAINER(s->box4), s->box_rooms);
    gtk_box_pack_start(GTK_BOX(s->box4), box2, TRUE, TRUE, 0);
    s->box_users2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(s->box_users), s->box_users2);
    gtk_container_add(GTK_CONTAINER(s->box4), s->box_users);
    gtk_box_pack_start(GTK_BOX(box), s->box4, TRUE, TRUE, 0);
    gtk_container_add(GTK_CONTAINER(box), box3);
    mx_little_window(s);
    gtk_widget_hide(s->a_window);
    gtk_widget_show_all(s->chat_window);
}
