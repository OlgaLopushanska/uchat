#include "uchat_server.h"

static t_serv *create_sr(int argc, char **argv);

static t_serv *delete_sr(t_serv *sr);

void init_standart_rooms(t_serv *sr);

t_serv *mx_init_struct(t_serv *sr, int argc, char **argv, int par) {
    sr = par ? create_sr(argc, argv) : delete_sr(sr);
    
    return sr;
}

static t_serv *create_sr(int argc, char **argv) {
    t_serv *sr = (t_serv*)malloc(sizeof(t_serv));


    sr->argc = argc;
    sr->argv = argv;
    init_standart_rooms(sr);
    pthread_mutex_init(&(sr->Lock), NULL);
    return sr;
}

static t_serv *delete_sr(t_serv *sr) {
    if(!sr)
        return NULL;
    pthread_mutex_destroy(&(sr->Lock));
    sr->rooms = (char **)mx_free2((void **)sr->rooms, sr->n_st_room);
    sr->id_rooms = (char **)mx_free2((void **)sr->id_rooms, sr->n_st_room);
    sr = mx_free(sr);
    return sr;
}

void init_standart_rooms(t_serv *sr) {
    sr->n_st_room = 8;
    sr->rooms = (char **)malloc(sizeof(char *) * sr->n_st_room);
    sr->id_rooms = (char **)malloc(sizeof(char *) * sr->n_st_room);
    sr->rooms[0] = mx_strdup("Reception");
    sr->id_rooms[0] = mx_strdup("Reception");
    sr->rooms[1] = mx_strdup("Невролог");
    sr->id_rooms[1] = mx_strdup("Neuro");
    sr->rooms[2] = mx_strdup("Хирург");
    sr->id_rooms[2] = mx_strdup("Surgery");
    sr->rooms[3] = mx_strdup("Педиатр");
    sr->id_rooms[3] = mx_strdup("Pediatr");
    sr->rooms[4] = mx_strdup("Психолог");
    sr->id_rooms[4] = mx_strdup("Psiholog");
    sr->rooms[5] = mx_strdup("Уролог");
    sr->id_rooms[5] = mx_strdup("Urolog");
    sr->rooms[6] = mx_strdup("Травматолог");
    sr->id_rooms[6] = mx_strdup("Travma");
    sr->rooms[7] = mx_strdup("Патологоанатом");
    sr->id_rooms[7] = mx_strdup("Patolog");


}