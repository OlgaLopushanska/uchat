#include "uchat_server.h"

static void change_name(char *sql_in, t_user *usr);

void mx_change_name(t_req *req, t_user *usr) {
    char *user = NULL;
    char *name = NULL;
    char *surname = NULL;
    char *sex = NULL;
    char *sql_in = NULL;

    user = mx_str_get_sub(&(req->req), 0, ':');
    name = mx_str_get_sub(&(req->req), 0, ':');
    surname = mx_str_get_sub(&(req->req), 0, ':');
    sex = mx_strdup(req->req);
    asprintf(&sql_in, "UPDATE Users SET Name = '%s', Surname = '%s', Sex = '%s' WHERE Login = '%s';", name, surname, sex, user);
    change_name(sql_in, usr);
    sql_in = mx_free(sql_in);



}

static void change_name(char *sql_in, t_user *usr) {
    char *err_msg = NULL;
    int rc = 0;
    
    rc = sqlite3_exec(usr->sr->db_u, sql_in, 0, 0, &err_msg);
    if(rc != SQLITE_OK)
        fprintf(stderr, "\033[31muchat_server:: connection %d - %s\033[0m\n", usr->con_id, sqlite3_errmsg(usr->sr->db_u));
}