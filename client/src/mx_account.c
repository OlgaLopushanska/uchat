#include "uchat.h"

static void exit_account(GtkWidget *button, gpointer data) {
    t_user *s = (t_user*)data;

    button = NULL;
    gtk_widget_destroy(s->a_window);
    s->close = 1;
    close(s->sfd);
}

static void change(GtkWidget *button, gpointer data) {
    t_user *s = (t_user*)data;
    char *num = NULL;
    char *request;

    button = NULL;
    s->name = mx_free(s->name);
    s->name = mx_strdup(gtk_entry_get_text(GTK_ENTRY(s->ap_entry1)));
    s->surname = mx_free(s->surname);
    s->surname = mx_strdup(gtk_entry_get_text(GTK_ENTRY(s->ap_entry2)));
    s->sex = mx_free(s->sex);
    s->sex = mx_strdup(gtk_entry_get_text(GTK_ENTRY(s->sex1)));
    s->sex = mx_strlen(s->sex) ? s->sex : mx_strdup("not_add");
    s->name = mx_strlen(s->name) ? s->name : mx_strdup("not_add");
    s->surname = mx_strlen(s->surname) ? s->surname : mx_strdup("not_add");
    asprintf(&request,"%s:%s:%s:%s", s->user, s->name, s->surname, s->sex);
    num = mx_get_current_num();
    mx_send_message(num, "3", request, s);
    if ((s->sex)[0] == 'w')
        s->prof_image = gtk_image_new_from_file("avatar3.jpg");
    else
        s->prof_image = gtk_image_new_from_file("avatar4.jpg");
    gtk_label_set_text(GTK_LABEL(s->a_label4), s->name);
    gtk_label_set_text(GTK_LABEL(s->a_label6), s->surname);
    gtk_widget_destroy(s->ap_window);
}

static void delete(GtkWidget *button, gpointer data) {
    t_user *s = (t_user*)data;
    
    button = NULL;
    mx_send_message("123", "12", s->user, s);
    gtk_widget_destroy(s->a_window);
    s->close = 1;
    close(s->sfd);
}

static void print(GtkWidget *button, gpointer data) {
    t_user *s = (t_user*)data;
    GtkWidget *label1, *label2, *label3;
    GtkWidget *button1;
    GtkWidget *box;

    button = NULL;
    s->ap_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(s->ap_window), "Изменение профиля");
    gtk_window_set_position(GTK_WINDOW(s->ap_window), GTK_WIN_POS_CENTER);
    gtk_window_set_modal(GTK_WINDOW(s->ap_window), TRUE);
    gtk_window_set_default_size(GTK_WINDOW(s->ap_window),200, 100);
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_container_add(GTK_CONTAINER(s->ap_window), box);
    gtk_container_set_border_width(GTK_CONTAINER(s->ap_window), 20);
    label1 = gtk_label_new("Введите имя");
    label2 = gtk_label_new("Введите фамилию");
    label3 = gtk_label_new("Введите свой пол: m - man, w - woman");
    s->ap_entry1 = gtk_entry_new();
    s->ap_entry2 = gtk_entry_new();
    s->sex1 = gtk_entry_new();
    gtk_entry_set_text(GTK_ENTRY(s->ap_entry1), s->name);
    gtk_entry_set_text(GTK_ENTRY(s->ap_entry2), s->surname);
    gtk_entry_set_text(GTK_ENTRY(s->sex1), s->sex);
    button1 = gtk_button_new_with_label("Ok");
    g_signal_connect(button1, "clicked", G_CALLBACK(change), s);
    gtk_container_add(GTK_CONTAINER(box), label1);
    gtk_container_add(GTK_CONTAINER(box), s->ap_entry1);
    gtk_container_add(GTK_CONTAINER(box), label2);
    gtk_container_add(GTK_CONTAINER(box), s->ap_entry2);
    gtk_container_add(GTK_CONTAINER(box), label3);
    gtk_container_add(GTK_CONTAINER(box), s->sex1);
    gtk_container_add(GTK_CONTAINER(box), button1);
    gtk_widget_show_all(s->ap_window);
}

void mx_account(gpointer data) {
    t_user *s = (t_user*)data;
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *button3;
    GtkWidget *button4;
    GtkWidget *button_box;
    GtkWidget *box;
    GtkWidget *box1;
    GtkWidget *box2;
    GtkWidget *box3;
    GtkWidget *label1;
    GtkWidget *label2;
    GtkWidget *label3;
    GtkWidget  *label5;

    s->a_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(s->a_window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(s->a_window), "Профиль");
    gtk_window_set_default_size(GTK_WINDOW(s->a_window), 700, 1000);
    gtk_window_set_modal(GTK_WINDOW(s->a_window), TRUE);
    GtkCssProvider *provider = gtk_css_provider_new();
    GtkStyleContext *context = gtk_widget_get_style_context(s->a_window);
if (s->theme == 1)
    gtk_css_provider_load_from_data(GTK_CSS_PROVIDER(provider),
        "* {\n background-color: RGB(4,9,82);\n }\n", -1, NULL);
else
    gtk_css_provider_load_from_data(GTK_CSS_PROVIDER(provider),
        "* {\n background-color: RGB(100,166,247);\n }\n", -1, NULL);
    gtk_style_context_add_provider (context, GTK_STYLE_PROVIDER (provider),
        GTK_STYLE_PROVIDER_PRIORITY_USER);
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    button_box = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
    box1 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    box2 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    box3 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_box_set_spacing(GTK_BOX(button_box), 10);
    gtk_container_add(GTK_CONTAINER(s->a_window), box);
    gtk_container_set_border_width(GTK_CONTAINER(s->a_window), 20);
    button1 = gtk_button_new_with_label ("Изменить имя или фамилию");
    button2 = gtk_button_new_with_label ("Удалить профиль");
    button3 = gtk_button_new_with_label("Перейти в чат");
    button4 = gtk_button_new_with_label("Выйти");
    label1 = gtk_label_new("Логин");
    label2 = gtk_label_new(s->user);
    label3 = gtk_label_new("Имя");
    if (s->name == NULL)
        s->a_label4 = gtk_label_new("");
    else 
        s->a_label4 = gtk_label_new(s->name);
    label5 = gtk_label_new("Фамилия");
    if (s->surname == NULL)
        s->a_label6 = gtk_label_new("");
    else
        s->a_label6 = gtk_label_new(s->surname);
    if ((s->sex)[0] == 'w')
        s->prof_image = gtk_image_new_from_file("avatar3.jpg");
    else
        s->prof_image = gtk_image_new_from_file("avatar4.jpg");
    g_signal_connect(button1, "clicked", G_CALLBACK(print), s);
    g_signal_connect(button2, "clicked", G_CALLBACK(delete), s);
    g_signal_connect(button3, "clicked", G_CALLBACK(mx_chat_main), s);
    g_signal_connect(button4, "clicked", G_CALLBACK(exit_account), s);
    gtk_container_add(GTK_CONTAINER(box), s->prof_image);
    gtk_container_add(GTK_CONTAINER(box1), label1);
    gtk_container_add(GTK_CONTAINER(box1), label2);
    gtk_container_add(GTK_CONTAINER(box2), label3);
    gtk_container_add(GTK_CONTAINER(box2), s->a_label4);
    gtk_container_add(GTK_CONTAINER(box3), label5);
    gtk_container_add(GTK_CONTAINER(box3), s->a_label6);
    gtk_container_add(GTK_CONTAINER(button_box), button1);
    gtk_container_add(GTK_CONTAINER(button_box), button2);
    gtk_container_add(GTK_CONTAINER(button_box), button3);
    gtk_container_add(GTK_CONTAINER(button_box), button4);
    gtk_container_add(GTK_CONTAINER(box), box1);
    gtk_container_add(GTK_CONTAINER(box), box2);
    gtk_container_add(GTK_CONTAINER(box), box3);
    gtk_container_add(GTK_CONTAINER(box), button_box);
    gtk_widget_hide(s->main_window);
    gtk_widget_hide(s->e_window);
    gtk_widget_show_all(s->a_window);
}
