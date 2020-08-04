#include "uchat.h"

void *mx_run_interface(void *data) {
    t_user *s = (t_user*)data;
    int status = 0;

    s->app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(s->app, "activate", G_CALLBACK(mx_headband), s);
    status = g_application_run(G_APPLICATION(s->app), 0, NULL);
    g_object_unref(s->app); 
    return 0;
}
