#include "uchat_server.h"

static void add_new_room(char *user, char *room, char *id_room, t_user *usr);

void mx_add_user_to_room(char *new_user, char *room, char *id_room, t_user *usr) {
    char *sql_in = NULL;
    char *err_msg = NULL;
    int rc = 0;

    asprintf(&sql_in, 
        "CREATE TABLE IF NOT EXISTS %s (Id INTEGER PRIMARY KEY AUTOINCREMENT, User TEXT, Can_del INT);"
        "INSERT INTO %s (User, Can_del) VALUES ('%s', 0);", id_room, id_room, new_user);
    rc = sqlite3_exec(usr->sr->db_ur, sql_in, 0, 0, &err_msg);
    if(rc != SQLITE_OK)
        fprintf(stderr, "\033[33muchat_server:: data base %s\033[0m\n", sqlite3_errmsg(usr->sr->db_r));
    sql_in = mx_free(sql_in);
    if(room)
        add_new_room(new_user, room, id_room, usr);
}

static void add_new_room(char *user, char *room, char *id_room, t_user *usr) {
    char *sql_in = NULL;
    int rc = 0;
    char *err_msg = NULL;
    t_db *tdb = mx_int_struct_tdb(NULL, 1);

    tdb->db = usr->sr->db_r;
    tdb->what_find = mx_strdup("*");
    tdb = mx_find_id(user, "IDROOM", id_room , tdb);
    if(!tdb->argc){

        asprintf(&sql_in, 
            "CREATE TABLE IF NOT EXISTS %s (Id INTEGER PRIMARY KEY AUTOINCREMENT, Room TEXT, IDRoom TEXT, Can_del INT);"
            "INSERT INTO %s (Room, IDRoom, Can_del) VALUES ('%s', '%s', 0);",
            user, user, room, id_room);
        rc = sqlite3_exec(usr->sr->db_r, sql_in, 0, 0, &err_msg);
        if(rc != SQLITE_OK)
            fprintf(stderr, "\033[33muchat_server:: data base %s\033[0m\n", sqlite3_errmsg(usr->sr->db_r));
        sql_in = mx_free(sql_in);
    }
    tdb = mx_int_struct_tdb(NULL, 1);

}
