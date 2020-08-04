#include "uchat_server.h"

t_db *mx_find_id(char *table, char* colum, char *value, t_db *tdb) {
    char *sql_in = NULL;

    asprintf(&sql_in, "SELECT %s FROM %s WHERE %s = '%s';", tdb->what_find, table, colum, value);
    mx_db_send_req(tdb->db, sql_in, mx_get_data, tdb);

    mx_free(sql_in);

    return tdb;

    //db_s.par1 = sqlite3_prepare_v2()

}

