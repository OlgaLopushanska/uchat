#include "uchat_server.h"

static void find_user(char *user, char *sql_req, t_req *req, t_user *usr);

static void add_standart_rooms (char *user, t_user *usr);

void mx_add_new_user(t_req *req, t_user *usr) {
    char *user = NULL;
    char *pass = NULL;
    char *email = NULL;
    char *sql_in = NULL;

    user = mx_str_get_sub(&(req->req), 0, ':');
    pass = mx_str_get_sub(&(req->req), 0, ':');
    email = mx_strdup(req->req);
    asprintf(&sql_in, "INSERT INTO Users(Login,Password,Email,Name,Surname,Sex,Deleted) VALUES ('%s','%s','%s','not_set','not_set','not_set',0);", user, pass, email);
    /*char *err_msg = NULL;
sqlite3_exec(usr->sr->db_u, sql_in, 0, 0, &err_msg);*/

    find_user(user, sql_in, req, usr);
    sql_in = mx_free(sql_in);



}

static void find_user(char *user, char *sql_req, t_req *req, t_user *usr) {
    //char *sql_in = NULL;
    char *err_msg = NULL;
    int rc = 0;
    t_db *tdb = mx_int_struct_tdb(NULL, 1);
    
    /*asprintf(&sql_in, "SELECT * FROM Users WHERE Login = '%s';", user);
    rc = sqlite3_exec(usr->sr->db_u, sql_in, mx_find_in_db, (void *)db, &err_msg);
    sql_in = mx_free(sql_in);*/
    tdb->db = usr->sr->db_u;
    tdb->argc = 0;
    tdb->what_find = mx_strdup("*");
    tdb = mx_find_id("Users", "Login", user , tdb);
    if(tdb->argc)
        mx_send_message(req->num, "1", "User already exsist", usr);
    else {
        rc = sqlite3_exec(usr->sr->db_u, sql_req, 0, 0, &err_msg);
        if(rc == SQLITE_OK) {
            mx_send_message(req->num, "1", "OK New user create", usr);
            add_standart_rooms(user, usr); 
        }
        else
            mx_send_message(req->num, "1", "Error DB ad New user", usr);
    }
    tdb = mx_int_struct_tdb(tdb, 0);
}

static void add_standart_rooms(char *user, t_user *usr) {
    char *id_room = NULL;
    char *num = NULL;
    int i = 0;

    for (i = 0; i < usr->sr->n_st_room; i++) {
        num = mx_get_current_num();
        asprintf(&id_room, "%s_%s_%s", usr->sr->id_rooms[i], user, num);
        mx_add_new_room(user, usr->sr->rooms[i], id_room, usr);
        mx_add_user_to_room(usr->sr->id_rooms[i], usr->sr->rooms[i], id_room, usr);
        num = mx_free(num);
        id_room = mx_free(id_room);
    }
    num = mx_free(num);
}