#include "uchat_server.h"

char *mx_strdup(const char *s1) {
    int size = 0;
    char *t = NULL;

    if(!s1)
        return NULL;
    size = mx_strlen(s1);
    t = mx_strnew(size);
    if (t)
        mx_strcpy(t, s1);
    return t;
}
