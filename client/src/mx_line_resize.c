#include "uchat.h"

char *mx_line_resize(char *in, int size) {
    int l = 0;
    int i = 0;
    int n = 0;
    int t[2] = {0, 0};
    char *res = NULL;

    if (!in)
        return in;
    l = mx_strlen(in);
    t[1] = l + 10;
    res = mx_strnew(t[1]);
    for (i = 0; i < l; i++) {
        n = in[i] == '\n' ? 0 : n;
        if (n >= size) {
            res[t[0]] = '\n';
            (t[1])++;
            (t[0])++;
            res = (char *)realloc(res, sizeof(char *) * t[1]);
            n = 0;
        }
            res[t[0]] = in[i];
            n++;
            (t[0])++;
            res[t[0]] = '\0';
    }   
    free(in);
    return res;
}
