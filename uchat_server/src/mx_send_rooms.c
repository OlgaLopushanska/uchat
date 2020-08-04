#include "uchat_server.h"

char*  mx_send_rooms(char *user, t_user *usr) {
    t_db *tdb = mx_int_struct_tdb(NULL, 1);
    int res = 0;
    char *err_msg = NULL;
    char *sql_in = NULL;
    int i = 0;

    tdb->db = usr->sr->db_r;
    tdb->argc = 0;
    asprintf(&sql_in, "SELECT Room, IDRoom FROM %s;", user);
    res = sqlite3_exec(usr->sr->db_r, sql_in, mx_get_data, (void *)tdb, &err_msg);
    if(res != SQLITE_OK)
        fprintf(stderr, "\033[31muchat_server:: connection %d - %s\033[0m\n", usr->cfd, sqlite3_errmsg(usr->sr->db_r));

    mx_free(sql_in);
    if (tdb->n_row) {
        asprintf(&sql_in, "%d", tdb->n_row);
        for (i = 0; i < tdb->n_row; i++) {
            sql_in = mx_strjoin(sql_in, ":");
            sql_in = mx_strjoin(sql_in, tdb->cpar3[i][0]);
            sql_in = mx_strjoin(sql_in, ":");
            sql_in = mx_strjoin(sql_in, tdb->cpar3[i][1]);
        }
    }
    else
        asprintf(&sql_in, "0:");

    return sql_in;

}
