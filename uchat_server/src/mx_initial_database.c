#include "uchat_server.h"

static void close_err_db(sqlite3 *db, t_serv *sr);

static void prime_users_init (t_serv *sr);

void mx_initial_database(t_serv *sr){
    char *err_msg = NULL;

    char *connect = "DROP TABLE IF EXISTS Connect;" 
                    "CREATE TABLE Connect (Id INTEGER PRIMARY KEY AUTOINCREMENT, Login TEXT, User_Id INT, Socket INT, Pr1 INT);";
    char *users = //"DROP TABLE IF EXISTS Users;" 
                  "CREATE TABLE IF NOT EXISTS Users (Id INTEGER PRIMARY KEY AUTOINCREMENT, Login TEXT, Password TEXT, Email TEXT, Name TEXT, Surname TEXT, Sex TEXT, Rooms TEXT, Deleted INT);";
//    char *rooms = //"DROP TABLE IF EXISTS Rooms;" 
//                  "CREATE TABLE Rooms (Id INTEGER PRIMARY KEY AUTOINCREMENT, Name TEXT, Users TEXT, History TEXT, Can_del INT);";
//    char *hist = "DROP TABLE IF EXISTS hist;";

    if (sqlite3_open("./Users.db", &(sr->db_u)) != SQLITE_OK)
        close_err_db(sr->db_u, sr);        
    if (sqlite3_open("./Connect.db", &(sr->db_c)) != SQLITE_OK)
        close_err_db(sr->db_c, sr);        
    if (sqlite3_open("./Rooms.db", &(sr->db_r)) != SQLITE_OK)
        close_err_db(sr->db_r, sr);        
    if (sqlite3_open("./Hist.db", &(sr->db_h)) != SQLITE_OK)
        close_err_db(sr->db_h, sr);      
    if (sqlite3_open("./Users_in_room.db", &(sr->db_ur)) != SQLITE_OK)
        close_err_db(sr->db_ur, sr);        

    if(sqlite3_exec(sr->db_c, connect, 0, 0, &err_msg) != SQLITE_OK)
        fprintf(stderr, "\033[33muchat_server:: data base %s\033[0m\n", sqlite3_errmsg(sr->db_c));
    if(sqlite3_exec(sr->db_u, users, 0, 0, &err_msg) != SQLITE_OK)
        fprintf(stderr, "\033[33muchat_server:: data base %s\033[0m\n", sqlite3_errmsg(sr->db_u));
//    if(sqlite3_exec(sr->db_r, rooms, 0, 0, &err_msg) != SQLITE_OK)
//        fprintf(stderr, "\033[33muchat_server:: data base %s\033[0m\n", sqlite3_errmsg(sr->db_r));
//    if(sqlite3_exec(sr->db_h, hist, 0, 0, &err_msg) != SQLITE_OK)
//        fprintf(stderr, "\033[31muchat_server:: fault open data base %s\033[0m\n", sqlite3_errmsg(sr->db_h));

    prime_users_init (sr);

}

static void close_err_db(sqlite3 *db, t_serv *sr) {
    fprintf(stderr, "\033[31muchat_server:: fault open data base %s\033[0m\n", sqlite3_errmsg(db));
    sqlite3_close(sr->db_c);
    sqlite3_close(sr->db_u);
    sqlite3_close(sr->db_r);
    sqlite3_close(sr->db_h);
    exit(1);
}

static void prime_users_init (t_serv *sr) {
    char *err_msg = NULL;
    int rc = 0;
    char *sql_in = NULL;
    t_db *tdb = NULL;
    int i = 0;
    

    for (i = 0; i < sr->n_st_room; i++) {
        tdb = mx_int_struct_tdb(NULL, 1);
        tdb->db = sr->db_u;
        tdb->argc = 0;
        tdb->what_find = mx_strdup("*");
        tdb = mx_find_id("Users", "Login", sr->id_rooms[i], tdb);
        if(!(tdb->argc))
            asprintf(&sql_in, "INSERT INTO Users(Login,Password,Email,Name,Surname,Sex,Deleted) VALUES ('%s','123','1@gmail.com','not_set','not_set','not_set',0);", sr->id_rooms[i]);
            rc = sqlite3_exec(sr->db_u, sql_in, 0, 0, &err_msg);
            sql_in = mx_free(sql_in);
            if(rc == SQLITE_OK)
                fprintf(stdout,"User %s is created\n", sr->rooms[i]);
            else
                fprintf(stderr,"Error DB ad New user - %s", sqlite3_errmsg(sr->db_u));
        tdb = mx_int_struct_tdb(tdb, 0);
    }
}

