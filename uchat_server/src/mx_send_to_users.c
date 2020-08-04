#include "uchat_server.h"

static void sending(t_db *tdb_in, char *message, t_user *usr);

void mx_send_to_users(char *id_room, char *message, t_user *usr) {
    t_db *tdb = mx_int_struct_tdb(NULL, 1);
    int res = 0;
    char *err_msg = NULL;
    char *sql_in = NULL;

    tdb->db = usr->sr->db_ur;
    asprintf(&sql_in, "SELECT User FROM %s;", id_room);
    res = sqlite3_exec(usr->sr->db_ur, sql_in, mx_get_data, (void *)tdb, &err_msg);
    if(res != SQLITE_OK)
        fprintf(stderr, "\033[31muchat_server:: connection %d - %s\033[0m\n", usr->cfd, sqlite3_errmsg(usr->sr->db_ur));
    mx_free(sql_in);
    if (tdb->n_row)
        sending(tdb, message, usr);
    
    tdb = mx_int_struct_tdb(NULL, 0);

}

static void sending(t_db *tdb_in, char *message, t_user *usr) {
    t_db *tdb = NULL;
    int i = 0;
    int res = 0;
    //char *err_msg = NULL;
    char *sql_in = NULL;
    int socket = 0;


    for (i = 0; i < tdb_in->n_row; i++) {
        tdb = mx_int_struct_tdb(NULL, 1);
        tdb->db = usr->sr->db_c;
        asprintf(&sql_in, "SELECT Socket FROM Connect WHERE Login = '%s';", tdb_in->cpar3[i][0]);
        res = sqlite3_exec(usr->sr->db_c, sql_in, mx_get_data, (void *)tdb, NULL);
        mx_free(sql_in);
        if (tdb->n_row) {
            socket = mx_atoi(tdb->cpar3[0][0]);
            asprintf(&sql_in,"0:1001:%s", message);
            res = mx_strlen(sql_in);
            if (send(socket, sql_in, res, 0) != res)
                fprintf(stderr, "\033[31muchat_server:: error sending message - socket \"%d\"\033[0m\n", usr->cfd);//не удалось соедінітся с сокетом
            sql_in = mx_free(sql_in);
        }
        tdb = mx_int_struct_tdb(NULL, 0);
    }


}
