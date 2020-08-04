#include "uchat.h"

void mx_del_room(GtkWidget *button, gpointer data) {
    t_user *s = (t_user*)data;
    char *message = NULL;
    char *num = mx_get_current_num();
    t_req * req = NULL;

    button = NULL;
    if ((s->c_room >= 0) || (s->c_room < s->b_num_rooms)) {
        asprintf(&message,"%s:%s", s->user, s->rooms[s->c_room][1]);
        mx_send_message(num, "8", message, s);
        message = mx_free(message);
        req = mx_recive_message(num, s);
        mx_button_rooms_get(req, s, 1);
        req = mx_free_struct_req(req);
        gtk_widget_show_all(s->chat_window);
        s->c_room = -1;
    }    
    num = mx_free(num);
}
