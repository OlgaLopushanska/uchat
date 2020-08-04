#include "uchat_server.h"

int mx_get_data (void *data, int argc, char **argv, char **colName) {
    t_db *tdb = (t_db *)data;
    int i = 0;

    if (argv[0] && argc) {
        (tdb->n_row)++;
        tdb->cpar3 = (char ***)realloc(tdb->cpar3, sizeof(char **) * tdb->n_row);
        tdb->argc = argc;
        tdb->cpar3[(tdb->n_row) - 1] = (char **)malloc(sizeof(char *) * argc);
        for (i = 0; i < argc; i++)
            tdb->cpar3[(tdb->n_row) - 1][i] = mx_strdup(argv[i]);
    }
   return 0;
}
