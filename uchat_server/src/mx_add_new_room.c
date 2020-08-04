#include "uchat_server.h"

void mx_add_new_room(char *user, char *room, char *id_room, t_user *usr) {
    char *sql_in = NULL;
    int rc = 0;
    char *err_msg = NULL;

    asprintf(&sql_in, 
        "CREATE TABLE IF NOT EXISTS %s (Id INTEGER PRIMARY KEY AUTOINCREMENT, Room TEXT, IDRoom TEXT, Can_del INT);"
        "INSERT INTO %s (Room, IDRoom, Can_del) VALUES ('%s', '%s', 0);",
        user, user, room, id_room);
    rc = sqlite3_exec(usr->sr->db_r, sql_in, 0, 0, &err_msg);
    if(rc != SQLITE_OK)
        fprintf(stderr, "\033[33muchat_server:: data base %s\033[0m\n", sqlite3_errmsg(usr->sr->db_r));
    mx_add_user_to_room(user, NULL, id_room, usr);
}
