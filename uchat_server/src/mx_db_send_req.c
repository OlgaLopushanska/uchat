#include "uchat_server.h"

void mx_db_send_req(sqlite3 *db, char *sql_req,
                    int (*func)(void *, int , char **, char **), t_db *tdb) {
    int rc = 0;
    char *err_msg = NULL;

    rc =  sqlite3_exec(db, sql_req, func, (void *)tdb, &err_msg);
    if(rc != SQLITE_OK && rc != SQLITE_ABORT)
        fprintf(stderr, "\033[31muchat_server:: database - %s\033[0m\n", sqlite3_errmsg(db));

}
