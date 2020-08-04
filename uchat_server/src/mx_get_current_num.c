#include "uchat_server.h"

char *mx_get_current_num() {
    struct timeval dat;
    char *res = NULL;
    char *res_mil = NULL;
    
    gettimeofday(&dat, NULL);
    res = mx_itoa(dat.tv_sec);
    res = mx_strjoin(res, "_");
    res_mil = mx_itoa(dat.tv_usec);
    res = mx_strjoin(res, res_mil);
    free(res_mil);
    return res;
}
