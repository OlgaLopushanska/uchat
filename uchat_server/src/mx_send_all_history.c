#include "uchat_server.h"

void send_line(t_req *req_in, t_user *usr);

void mx_send_all_history(t_req *req, t_user *usr) {
    char *sql_in = NULL;
    char *id_room = NULL;
    t_db *tdb = mx_int_struct_tdb(NULL, 1);

    if(req->type == 10) {
        id_room = mx_strdup(req->req);
        asprintf(&sql_in, "SELECT User, Time, Message FROM %s;", id_room);
        mx_db_send_req(usr->sr->db_h, sql_in, mx_get_data, tdb);
        mx_free(sql_in);
        asprintf(&sql_in, "%d", tdb->n_row);
        mx_send_message(req->num, "11", sql_in, usr);
        sql_in = mx_free(sql_in);
        tdb = mx_int_struct_tdb(NULL, 0);
    }
    if(req->type == 11) {
        send_line(req, usr);
    }
}

void send_line(t_req *req, t_user *usr) {
    char *id_room = NULL;
    //int i = 0;
    t_db *tdb = mx_int_struct_tdb(NULL, 1);
    char *sql_in = NULL;

    id_room = mx_str_get_sub(&(req->req), 0, ':');
    asprintf(&sql_in, "SELECT User, Time, Message FROM %s WHERE Id = %s;", id_room, req->req);
    mx_db_send_req(usr->sr->db_h, sql_in, mx_get_data, tdb);
    sql_in = mx_free(sql_in);
    if (tdb->n_row) {
        asprintf(&sql_in, "%s:%s:%s", tdb->cpar3[0][0], tdb->cpar3[0][1], tdb->cpar3[0][2]);
        mx_send_message(req->num, "11", sql_in, usr);
        sql_in = mx_free(sql_in);
    }
    else
        mx_send_message(req->num, "11", "WRONG", usr);
    tdb = mx_int_struct_tdb(NULL, 0);
}