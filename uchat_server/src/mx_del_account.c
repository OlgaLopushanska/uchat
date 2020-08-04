#include "uchat_server.h"

void mx_del_account(t_req *req, t_user *usr) {
    char *user = NULL;
    char *sql_in = NULL;
    char *err_msg = NULL;
    int res = 0;

    user = mx_str_get_sub(&(req->req), 0, ':');
    
    asprintf(&sql_in, "DELETE FROM Users WHERE Login = '%s';", user);
    res = sqlite3_exec(usr->sr->db_u, sql_in, 0, 0, &err_msg);
    sql_in = mx_free(sql_in);
    if(res != SQLITE_OK)
        fprintf(stderr, "\033[31muchat_server:: connection %d - %s\033[0m\n", usr->cfd, sqlite3_errmsg(usr->sr->db_u));
    asprintf(&sql_in, "DROP TABLE IF EXISTS %s;", user);
    res = sqlite3_exec(usr->sr->db_r, sql_in, 0, 0, &err_msg);
    sql_in = mx_free(sql_in);
    if(res != SQLITE_OK)
        fprintf(stderr, "\033[31muchat_server:: connection %d - %s\033[0m\n", usr->cfd, sqlite3_errmsg(usr->sr->db_r));
    user = mx_free(user);
}