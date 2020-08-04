#include "uchat_server.h"

char *mx_str_get_sub (char **in, const char s1, const char s2) {
    char *sub = NULL;
    char *sub2 = NULL;
    int i1 = -1;
    int i2 = mx_strlen(*in) + 1;

    if(s1 != 0)
        i1 = mx_get_char_index(*in, s1);
    if(s2 != 0)
        i2 = mx_get_char_index(*in + i1 + 1, s2);
    sub = mx_strndup((*in) + i1 + 1, i2);
    if ((*in)[i1 + i2] != '\0')
        sub2 = mx_strdup(*in +i1 + i2 +2);
    *in = mx_free(*in);
    *in = sub2;
    return sub;
}
