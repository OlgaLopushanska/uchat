#include "uchat_server.h"

int mx_find_in_db(void *data, int argc, char **argv, char **colName) {
    t_db *db = (t_db *)data;

    if(argv[0])
        db->cpar1 = mx_strdup(argv[0]);
    //db->par1 = argc;
    //db->par2 = 5;


    return 0;
}