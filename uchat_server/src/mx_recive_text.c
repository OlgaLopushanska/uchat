#include "uchat_server.h"

void mx_recive_text(t_req *req, t_user *usr) {
    char *message = NULL;
    char *user = NULL;
    char *id_room = NULL;
    char *text = NULL;
    char *time = NULL;
    char *sql_in = NULL;
    int rc = 0;

    message = mx_strdup(req->req);
    user = mx_str_get_sub(&(req->req), 0, ':');
    id_room = mx_str_get_sub(&(req->req), 0, ':');
    time = mx_str_get_sub(&(req->req), 0, ':');
    text = mx_str_get_sub(&(req->req), 0, ':');
    asprintf(&sql_in, 
        "CREATE TABLE IF NOT EXISTS %s (Id INTEGER PRIMARY KEY AUTOINCREMENT, User TEXT, Time TEXT, Message TEXT);"
        "INSERT INTO %s (User, Time, Message) VALUES ('%s','%s','%s');", id_room, id_room, user, time, text);
    rc = sqlite3_exec(usr->sr->db_h, sql_in, 0, 0, NULL);
    if(rc != SQLITE_OK)
        fprintf(stderr, "\033[33muchat_server:: data base %s\033[0m\n", sqlite3_errmsg(usr->sr->db_r));
    sql_in = mx_free(sql_in);

    mx_send_to_users(id_room, message, usr);


    user = mx_free(user);
    id_room = mx_free(user);
    text = mx_free(text);
    time = mx_free(time);
    message = mx_free(message);
}
