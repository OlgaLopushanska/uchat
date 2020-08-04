#include "uchat.h"

void mx_send_text_line(GtkWidget *button, gpointer data) {
    t_user *s = (t_user*)data;
    char *line = NULL;
    time_t ttime = time(NULL);
    char *c_time = ctime(&ttime);
    char *mesage = NULL;
    int i = 0;

    button = NULL;
    for (i = 0; i < mx_strlen(c_time); i++)
        if(c_time[i] == ':')
            c_time[i] = '/';
    if ((s->c_room >= 0) || (s->c_room < s->b_num_rooms)) {
        line = mx_strdup(gtk_entry_get_text(GTK_ENTRY(s->chat_entry)));
        gtk_entry_set_text(GTK_ENTRY(s->chat_entry), "");
        if (mx_strlen(line) > 0) {
            asprintf(&mesage, "%s:%s:%s:%s", s->user, s->rooms[s->c_room][1],
                c_time, line);
            mx_send_message("0", "9",mesage, s);
            mesage = mx_free(mesage);
        }
    }
}
