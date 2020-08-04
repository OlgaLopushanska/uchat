#include "uchat_server.h"

static void find_user(char *user, char *pass, t_req *req, t_user *usr);

static bool user_already_connect(char *user, t_user *usr);

void mx_enter_user(t_req *req, t_user *usr) {
    char *user = NULL;
    char *pass = NULL;
    char *sql_in = NULL;

    user = mx_str_get_sub(&(req->req), 0, ':');
    pass = mx_strdup(req->req);
    /*char *err_msg = NULL;
sqlite3_exec(usr->sr->db_u, sql_in, 0, 0, &err_msg);*/

    find_user(user, pass, req, usr);
    sql_in = mx_free(sql_in);



}

static void find_user(char *user, char *pass, t_req *req, t_user *usr) {
    t_db *tdb = mx_int_struct_tdb(NULL, 1);
    char *message = NULL;
    
    tdb->db = usr->sr->db_u;
    //tdb->par1 = 0;
    tdb->what_find = mx_strdup("Password, Name, Surname, Sex");
    tdb = mx_find_id("Users", "Login", user , tdb);
    if(!tdb->argc)
        mx_send_message(req->num, "2", "Cant find user", usr);
    else if(mx_strcmp(pass, tdb->cpar3[0][0]) != 0)
        mx_send_message(req->num, "2", "Wrong Password", usr);
    else{
        if(user_already_connect(user, usr))
            asprintf(&message, "User already connected");
        else{
            asprintf(&message, "WelCome!!!:%s:%s:%s",tdb->cpar3[0][1], tdb->cpar3[0][2], tdb->cpar3[0][3]);
            mx_send_message(req->num, "2", message, usr);
            message = mx_free(message);
            message = mx_send_rooms(user, usr);           
        }
        mx_send_message(req->num, "2", message, usr);
        message = mx_free(message);
    }
    tdb = mx_free(tdb);

}

static bool user_already_connect(char *user, t_user *usr) {
    t_db *tdb = mx_int_struct_tdb(NULL, 1);
    char *sql_in = NULL;
    int res = 0;
    char *err_msg = NULL;

    tdb->db = usr->sr->db_c;
    tdb->argc = 0;
    tdb->what_find = mx_strdup("*");
    tdb = mx_find_id("Connect", "Login", user , tdb);
    res = tdb->argc;
    tdb = mx_int_struct_tdb(tdb, 0);
    if(!res) {
        asprintf(&sql_in, "UPDATE Connect SET Login = '%s' WHERE Socket = %d;", user, usr->cfd);
        res = sqlite3_exec(usr->sr->db_c, sql_in, 0, 0, &err_msg);
        sql_in = mx_free(sql_in);
        if(res != SQLITE_OK)
            fprintf(stderr, "\033[31muchat_server:: connection %d - %s\033[0m\n", usr->cfd, sqlite3_errmsg(usr->sr->db_c));
        return false;
    }
    else
        return true;
}

