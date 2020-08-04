#include "uchat.h"

GtkWidget *mx_create_scroll(GtkWidget *widg, int X, int Y, t_user *s) {
    widg = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_set_border_width(GTK_CONTAINER (widg), 10);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW (widg),
        GTK_POLICY_NEVER, GTK_POLICY_ALWAYS);
    gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW (widg), X);
    gtk_scrolled_window_set_min_content_height(GTK_SCROLLED_WINDOW (widg), Y);
    gtk_scrolled_window_set_max_content_width(GTK_SCROLLED_WINDOW (widg), X);
    gtk_scrolled_window_set_max_content_height(GTK_SCROLLED_WINDOW (widg), Y);
    mx_add_style(widg, 1, s);
    return widg;
}
