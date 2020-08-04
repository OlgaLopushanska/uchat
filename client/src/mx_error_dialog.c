#include "uchat.h"

void mx_error_dialog(GtkWidget *button, gpointer *data, char *message) {
    GtkWidget *window;
    GtkWidget *label;
    GtkWidget *button2;
    GtkWidget *box;

    button = NULL;
    data = NULL;
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Ошибка ввода");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_modal(GTK_WINDOW(window), TRUE);
    gtk_window_set_default_size(GTK_WINDOW(window),200, 100);
    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 20);
    gtk_container_add(GTK_CONTAINER(window), box);
    gtk_container_set_border_width(GTK_CONTAINER(window), 20);
    label = gtk_label_new("");
    gtk_label_set_text(GTK_LABEL(label), message);
    button2 = gtk_button_new_with_label("Ok");
    g_signal_connect_swapped(button2, "clicked",
        G_CALLBACK(gtk_widget_destroy), window);
    gtk_container_add(GTK_CONTAINER(box), label);
    gtk_container_add(GTK_CONTAINER(box), button2);
    gtk_widget_show_all(window);
}
