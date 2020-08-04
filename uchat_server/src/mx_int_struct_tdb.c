#include "uchat_server.h"

static t_db *create_tdb(t_db *tdb);

static t_db *delete_tdb(t_db *tdb);

t_db *mx_int_struct_tdb(t_db *tdb, int par) {
    tdb = par ? create_tdb(tdb) : delete_tdb(tdb);

    return tdb;
}

static t_db *create_tdb(t_db *tdb) {
    tdb = (t_db *)malloc(sizeof(t_db));
    tdb->par1 = 0;
    tdb->par2 = 0;
    tdb->par3 = 0;
    tdb->cpar1 = NULL;
    tdb->n_row = 0;
    tdb->argc = 0;
    tdb->cpar3 = NULL;
    tdb->what_find = NULL;
    return tdb;
}

static t_db *delete_tdb(t_db *tdb) {
    int i = 0;

    if(!tdb)
        return NULL;
    tdb->cpar1 = mx_free(tdb->cpar1);
    if(tdb->cpar3) {
        for (i = 0; i < tdb->n_row; i++)
            tdb->cpar3[i] = (char **)mx_free2((void **)tdb->cpar3[i], tdb->argc);
        tdb->cpar3 = mx_free(tdb->cpar3);
    }
    tdb->what_find = mx_free(tdb->what_find);
    tdb = mx_free(tdb);
    return tdb;
}