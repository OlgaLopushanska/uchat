#include "uchat.h"

char *mx_str_get_sub (char **in, const char s1, const char s2) {
    char *sub = NULL;
    char *sub2 = NULL;
    int i1 = -1;
    int i2 = mx_strlen(*in) + 1;

    if (!(*in))
        return NULL;
    if (s1 != 0)
        i1 = mx_get_char_index(*in, s1);
    if (s2 != 0)
        i2 = mx_get_char_index(*in + i1 + 1, s2);
    if (i2 == -1)
        i2 = mx_strlen(*in + i1 + 1) + 1;
    sub = strndup((*in) + i1 + 1, i2);
    if ((*in)[i1 + i2] != '\0')
        sub2 = strdup(*in +i1 + i2 +2);
    *in = mx_free(*in);
    *in = sub2;
    return sub;
}
