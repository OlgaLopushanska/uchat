#include "uchat.h"

t_user *mx_free_struct(t_user *s) {
    int i = 0;
    
    pthread_mutex_unlock(&(s->Lock));
    s->b_num_rooms = 0;
    s->c_room = -1;
    for (i = 0; i < s->b_num_rooms && s->rooms[i]; i++)
        s->rooms[i] = (char **)mx_free2((void **)s->rooms[i], 2);
    s->rooms = mx_free(s->rooms);
    s->user_row = mx_free(s->user_row);
    s->user_lable = mx_free(s->user_lable);
    s->users = (char **)mx_free2((void **)s->users, s->n_users);
    s->user = mx_free(s->user);
    s->pass = mx_free(s->pass);
    s->pass2 = mx_free(s->pass2);
    s->email1 = mx_free(s->email1);
    s->sex = mx_free(s->sex);
    s->name = mx_free(s->name);
    s->surname = mx_free(s->surname);
    s->current = mx_free(s->current);
    s->snd = mx_free(s->snd);
    s->rcv = mx_free(s->rcv);
    free(s);
    return s;
}
