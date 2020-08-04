#include "uchat.h"

void mx_add_room(GtkWidget *button, gpointer *data) {
    t_user *s = (t_user*)data;
    char *message = NULL;

    if (button == s->but_c_new_chat)
        gtk_widget_show_all(s->window_new_room);
    else if (button == s->but_c_add_user) {
        if ((s->c_room < 0) || (s->c_room > s->b_num_rooms - 1)) {
            message = mx_strdup("Сначала войдите в комнату");
            mx_error_dialog(button, data, message);
            message = mx_free(message);
        }
        else
            gtk_widget_show_all(s->window_add_user);
    }
}
