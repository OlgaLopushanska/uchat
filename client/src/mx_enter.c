#include "uchat.h"

static void print_hello(GtkWidget *button, gpointer *data) {
    t_user *s = (t_user*)data;
    t_req *req = NULL;
    char *num = NULL;
    char *request = NULL;
    char *message = NULL;

    s->user = mx_strdup(gtk_entry_get_text(GTK_ENTRY(s->euser)));
    s->pass = mx_strdup(gtk_entry_get_text(GTK_ENTRY(s->epass)));
    asprintf(&request,"%s:%s", s->user, s->pass);
    num = mx_get_current_num();
    mx_send_message(num, "2", request, s);
    request = mx_free(request);
    req = mx_recive_message(num, s);
    if (mx_get_substr_index(req->req,"WelCome!!!") == 0) {
      s->name = mx_free(s->name);
      s->name = mx_str_get_sub (&req->req, ':', ':');
      s->surname = mx_free(s->surname);
      s->surname = mx_str_get_sub (&req->req, 0, ':');
      s->sex = mx_free(s->sex);
      s->sex = mx_strdup (req->req);
      req = mx_free_struct_req(req);
      req = mx_recive_message(num, s);
      mx_button_rooms_get(req, s, 1);
      req = mx_free_struct_req(req);
      mx_account(data);
    }
    else if(mx_get_substr_index(req->req,"Cant find user") == 0)
      message = mx_strdup("Пользовалель с указаным Логином не зарегистрирован");
    else if(mx_get_substr_index(req->req,"Wrong Password") == 0) 
      message = mx_strdup("Неверный пароль");
    else if(mx_get_substr_index(req->req,"User already connected") == 0) 
      message = mx_strdup("Пользователь с введенным логином уже выполнил вход");
    if(message) {
      mx_error_dialog(button, data, message);
      message = mx_free(message);
    }
    num = mx_free(num);
    req = mx_free_struct_req(req);
}

void mx_enter(GtkApplication *app, gpointer data) {
    GtkWidget *user;
    GtkWidget *pass;
    GtkWidget *button;
    GtkWidget *box;
    t_user *s = (t_user*)data;

    app = NULL;
    int length = 20;
    s->e_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(s->e_window), "Вход");
    gtk_window_set_position(GTK_WINDOW(s->e_window), GTK_WIN_POS_CENTER);
    gtk_window_set_modal(GTK_WINDOW(s->e_window), TRUE);
    gtk_window_set_default_size(GTK_WINDOW(s->e_window), 200, 200);
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_container_add(GTK_CONTAINER(s->e_window), box);
    gtk_container_set_border_width(GTK_CONTAINER(s->e_window), 20);
    user = gtk_label_new("Введите логин");
    pass = gtk_label_new("Введите пароль");
    s->euser = gtk_entry_new();
    s->epass = gtk_entry_new();
    gtk_entry_set_visibility(GTK_ENTRY(s->epass), FALSE);
    gtk_entry_set_invisible_char(GTK_ENTRY(s->epass), '$');
    gtk_entry_set_max_length(GTK_ENTRY(s->euser), length);
    gtk_entry_set_max_length(GTK_ENTRY(s->epass), length);
    button = gtk_button_new_with_label("Ok");
    g_signal_connect(button, "clicked", G_CALLBACK(print_hello), s);
    gtk_container_add(GTK_CONTAINER(box), user);
    gtk_container_add(GTK_CONTAINER(box), s->euser);
    gtk_container_add(GTK_CONTAINER(box), pass);
    gtk_container_add(GTK_CONTAINER(box), s->epass);
    gtk_container_add(GTK_CONTAINER(box), button);
    gtk_widget_show_all(s->e_window);
}

