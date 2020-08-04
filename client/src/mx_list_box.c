#include "uchat.h"

static void create_list(t_user *s);

static void delete_list(t_user *s);

void mx_list_box(t_user *s, int par) {
    par ? create_list(s) : delete_list(s);

}

static void select_row(GtkWidget *button, gpointer data) {
    t_user *s = (t_user *)data;
    int i = 0;

    for (i = 0; i < s->n_users && button != s->user_lable[i]; i++)
    ;
    s->c_user = i;
}

static void create_list(t_user *s) {
    int a = 0;

    s->user_lable = (GtkWidget **)malloc(sizeof(GtkWidget *) * s->n_users);
    for (a = 0; a < s->n_users; a++) {
        s->user_lable[a] = gtk_button_new_with_label(s->users[a]);
        g_signal_connect(s->user_lable[a], "clicked", G_CALLBACK(select_row), s);
        gtk_container_add(GTK_CONTAINER(s->box_users2), s->user_lable[a]);
    }
}

static void delete_list(t_user *s) {
    int a = 0;
 
    if (s->user_lable)
      for (a = 0; a < s->n_users; a++)
          gtk_widget_destroy(s->user_lable[a]); 
    s->users = (char **)mx_free2((void **)s->users, s->n_users);
    s->user_lable = mx_free(s->user_lable);
}
