#include "uchat.h"

void mx_redraw_room(t_req *req, t_user *s) {
    mx_button_rooms_get(req, s, 1);
    gtk_widget_show_all(s->chat_window);
}
