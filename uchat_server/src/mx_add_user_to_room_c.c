#include "uchat_server.h"

static void sending(char *user, t_user *usr);

void mx_add_user_to_room_c(t_req *req, t_user *usr) {
    char *message = NULL;
    char *user = NULL;
    char *id_room = NULL;
    char *room = NULL;
    t_db *tdb = mx_int_struct_tdb(NULL, 1);

    user = mx_str_get_sub(&(req->req), 0, ':');
    id_room = mx_str_get_sub(&(req->req), 0, ':');
    room = mx_str_get_sub(&(req->req), 0, ':');
    
    tdb->db = usr->sr->db_u;
    tdb->what_find = mx_strdup("Password, Name, Surname, Sex");
    tdb = mx_find_id("Users", "Login", user , tdb);
    if(!tdb->argc)
        mx_send_message(req->num, "6", "Cant find user", usr);
    else{
        mx_add_user_to_room(user, room, id_room, usr);
        message = mx_users_get_list(id_room, usr);
        mx_send_message(req->num, "6", message, usr);
        message = mx_free(message);
        sending(user, usr);
    }
    tdb = mx_int_struct_tdb(NULL, 0);

}

static void sending(char *user, t_user *usr) {
    t_db *tdb = NULL;
    int res = 0;
    char *message = NULL;
    //char *err_msg = NULL;
    char *sql_in = NULL;
    int socket = 0;

    tdb = mx_int_struct_tdb(NULL, 1);
    tdb->db = usr->sr->db_c;
    asprintf(&sql_in, "SELECT Socket FROM Connect WHERE Login = '%s';", user);
    res = sqlite3_exec(usr->sr->db_c, sql_in, mx_get_data, (void *)tdb, NULL);
    mx_free(sql_in);
    if (tdb->n_row) {
        socket = mx_atoi(tdb->cpar3[0][0]);
        message = mx_send_rooms(user, usr);
        asprintf(&sql_in,"0:1002:%s", message);
        res = mx_strlen(sql_in);
        if (send(socket, sql_in, res, 0) != res)
            fprintf(stderr, "\033[31muchat_server:: error sending message - socket \"%d\"\033[0m\n", usr->cfd);//не удалось соедінітся с сокетом
        sql_in = mx_free(sql_in);
    }
    tdb = mx_int_struct_tdb(NULL, 0);
    message = mx_free(message);
}
