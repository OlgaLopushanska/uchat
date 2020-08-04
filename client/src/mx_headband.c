#include "uchat.h"

static void main_exit(GtkWidget *button, gpointer data) {
    t_user *s = (t_user*)data;

    button = NULL;
    s->close = 0;
    g_application_quit(G_APPLICATION(s->app));
}

static void change(GtkWidget *button, gpointer data) {
    t_user *s = (t_user*)data;
    
    button = NULL;
    if (s->theme == 1)
        s->theme = 0;
    else
        s->theme = 1;
    GtkCssProvider *provider = gtk_css_provider_new();
    GtkStyleContext *context = gtk_widget_get_style_context(s->main_window);
    if (s->theme == 1)
        gtk_css_provider_load_from_data(GTK_CSS_PROVIDER(provider),
            "* {\n background-color: RGB(4,9,82);\n }\n", -1, NULL);
    else
        gtk_css_provider_load_from_data(GTK_CSS_PROVIDER(provider),
            "* {\n background-color: RGB(100,166,247);\n }\n", -1, NULL);
    gtk_style_context_add_provider(context,
        GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
}

void mx_headband(GtkApplication* app, gpointer data) {
    GtkWidget *button1;
    GtkWidget *button2;
    GtkWidget *button3;
    GtkWidget *button4;
    GtkWidget *button_box;
    GtkWidget *box;
    GtkWidget *image1;
    GtkWidget*image2;
    t_user *s = (t_user*)data;

    s->main_window = gtk_application_window_new(app);
    gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_position(GTK_WINDOW(s->main_window), GTK_WIN_POS_CENTER);
    gtk_window_set_title(GTK_WINDOW(s->main_window), "UCHAT");
    gtk_window_set_default_size(GTK_WINDOW(s->main_window), 700, 1000);
    GtkCssProvider *provider = gtk_css_provider_new();
    GtkStyleContext *context = gtk_widget_get_style_context(s->main_window);
    if (s->theme == 1)
        gtk_css_provider_load_from_data(GTK_CSS_PROVIDER(provider),
            "* {\n background-color: RGB(4,9,82);\n }\n", -1, NULL);
    else
        gtk_css_provider_load_from_data(GTK_CSS_PROVIDER(provider),
            "* {\n background-color: RGB(100,166,247);\n }\n", -1, NULL);
    gtk_style_context_add_provider (context,
        GTK_STYLE_PROVIDER (provider), GTK_STYLE_PROVIDER_PRIORITY_USER);
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    button_box = gtk_button_box_new(GTK_ORIENTATION_VERTICAL);
    gtk_box_set_spacing(GTK_BOX(button_box), 10);
    gtk_container_add(GTK_CONTAINER(s->main_window), box);
    gtk_container_set_border_width(GTK_CONTAINER(s->main_window), 20);
    button1 = gtk_button_new_with_label ("Зарегистрироваться");
    button2 = gtk_button_new_with_label ("Войти");
    button3 = gtk_button_new_with_label("Сменить тему");
    button4 = gtk_button_new_with_label("Выйти");
    image1 = gtk_image_new_from_file("image2.jpg");
    image2 = gtk_image_new_from_file("sprosi.jpg");
    g_signal_connect(button1, "clicked", G_CALLBACK(mx_register), s);
    g_signal_connect(button2, "clicked", G_CALLBACK(mx_enter), s);
    g_signal_connect(button3, "clicked", G_CALLBACK(change), s);
    g_signal_connect(button4, "clicked", G_CALLBACK(main_exit), s);
    gtk_container_add(GTK_CONTAINER(box), image1);
    gtk_container_add(GTK_CONTAINER(box), image2);
    gtk_container_add(GTK_CONTAINER(button_box), button4);
    gtk_container_add(GTK_CONTAINER(button_box), button1);
    gtk_container_add(GTK_CONTAINER(button_box), button2);
    gtk_container_add(GTK_CONTAINER(button_box), button3);
    gtk_container_add(GTK_CONTAINER(box), button_box);
    gtk_widget_show_all(s->main_window);
    pthread_mutex_lock(&(s->Lock));
    s->f_exit = 0;
    pthread_mutex_unlock(&(s->Lock));
}

