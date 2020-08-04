#include "uchat_server.h"

char *mx_users_get_list(char *id_room, t_user *usr) {
    t_db *tdb = mx_int_struct_tdb(NULL, 1);
    int res = 0;
    char *err_msg = NULL;
    char *sql_in = NULL;
    int i = 0;

    tdb->db = usr->sr->db_r;
    asprintf(&sql_in, "SELECT User FROM %s;", id_room);
    res = sqlite3_exec(usr->sr->db_ur, sql_in, mx_get_data, (void *)tdb, &err_msg);
    if(res != SQLITE_OK)
        fprintf(stderr, "\033[31muchat_server:: connection %d - %s\033[0m\n", usr->cfd, sqlite3_errmsg(usr->sr->db_ur));
    mx_free(sql_in);
    if (tdb->n_row) {
        asprintf(&sql_in, "%d", tdb->n_row);
        for (i = 0; i < tdb->n_row; i++) {
            sql_in = mx_strjoin(sql_in, ":");
            sql_in = mx_strjoin(sql_in, tdb->cpar3[i][0]);
        }
    }
    else
        asprintf(&sql_in, "0:");

    return sql_in;
}