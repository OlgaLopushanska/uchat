#include "uchat_server.h"

void mx_del_user_fr_room(t_req *req, t_user *usr) {
    char *message = NULL;
    char *user = NULL;
    char *id_room = NULL;
    char *sql_in = NULL;
    char *err_msg = NULL;
    int res = 0;

    user = mx_str_get_sub(&(req->req), 0, ':');
    id_room = mx_str_get_sub(&(req->req), 0, ':');
    
    asprintf(&sql_in, "DELETE FROM %s WHERE IDRoom = '%s';", user, id_room);
    res = sqlite3_exec(usr->sr->db_r, sql_in, 0, 0, &err_msg);
    sql_in = mx_free(sql_in);
    if(res != SQLITE_OK)
        fprintf(stderr, "\033[31muchat_server:: connection %d - %s\033[0m\n", usr->cfd, sqlite3_errmsg(usr->sr->db_r));
    asprintf(&sql_in, "DELETE FROM %s WHERE User = '%s';", id_room, user);
    res = sqlite3_exec(usr->sr->db_ur, sql_in, 0, 0, &err_msg);
    sql_in = mx_free(sql_in);
    if(res != SQLITE_OK)
        fprintf(stderr, "\033[31muchat_server:: connection %d - %s\033[0m\n", usr->cfd, sqlite3_errmsg(usr->sr->db_c));
    message = mx_users_get_list(id_room, usr);
    mx_send_message(req->num, "6", message, usr);
    message = mx_free(message);
    user = mx_free(user);
    id_room = mx_free(id_room);



}

