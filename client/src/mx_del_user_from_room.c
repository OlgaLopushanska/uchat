#include "uchat.h"

void mx_del_user_from_room(GtkWidget *button, gpointer data) {
    t_user *s = (t_user*)data;
    char *message = NULL;
    char *num = mx_get_current_num();
    t_req * req = NULL;

    button = NULL;
    if ((s->c_user >= 0) || (s->c_user < s->n_users)) {
        asprintf(&message,"%s:%s", s->users[s->c_user], s->rooms[s->c_room][1]);
        mx_send_message(num, "7", message, s);
        message = mx_free(message);
        req = mx_recive_message(num, s);
        mx_change_users_list(req, s);
        mx_list_box(s, 1); 
        req = mx_free_struct_req(req);
        gtk_widget_show_all(s->chat_window);
        s->c_user = -1;
    }    
    num = mx_free(num);    
}
