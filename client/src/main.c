#include "uchat.h"

int main(int argc, char **argv) {
    t_user *s = NULL;
    int ext = 1;

    if (argc >= 3) {
        gtk_init(NULL, NULL);
        while (ext == 1) {
            s = mx_struct_init(s);
            s->argv = argv;
            pthread_create(&(s->connect), NULL, mx_connect_to_server, (void*)s);
            pthread_mutex_init(&(s->Lock), NULL);
            s->f_exit = 1;
            pthread_create(&(s->sender), NULL, mx_sender, (void*)s);
            pthread_create(&(s->resiever), NULL, mx_reciever, (void*)s);
            mx_run_interface((void*)s);
            ext = s->close;
            pthread_cancel(s->connect);
            pthread_cancel(s->resiever);
            pthread_cancel(s->sender);
            s = mx_free_struct(s);
        }
        return 0;
    }
    else
        write(2, "uchat error:: didnt input ip adress or port\n", 44);
    return 0;
}
