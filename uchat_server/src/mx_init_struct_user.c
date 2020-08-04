#include "uchat_server.h"

static t_user *create_tuser(t_serv *sr, int cfd, int par);

static t_user *delete_tuser(t_user *usr);

t_user *mx_init_struct_user(t_user *usr, t_serv *sr, int cfd, int par) {
    usr = par ? create_tuser(sr, cfd, par) : delete_tuser(usr) ;

    return usr;
}

static t_user *create_tuser(t_serv *sr, int cfd, int par) {
    t_user *usr = (t_user*)malloc(sizeof(t_user));

    usr->sr = sr;
    usr->cfd = cfd;
    usr->snd = NULL;
    usr->rcv = NULL;
    pthread_mutex_init(&(usr->Lock), NULL);

    return usr;
}

static t_user *delete_tuser(t_user *usr) {
    if(!usr)
        return NULL;
    usr->snd = mx_free(usr->snd);
    usr->rcv = mx_free(usr->rcv);
    pthread_mutex_destroy(&(usr->Lock));
    usr = mx_free(usr);
    return usr;
}