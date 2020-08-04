#include "uchat.h"

char *mx_rec_edited(const int fd) {
    int bytes;
    int size = 65534;
    char *buf = NULL;

    if (fd < 0)
        return NULL;
    buf = mx_strnew(size);
    bytes = recv(fd, buf, size, 0);
    if (bytes <= 0)
        buf = mx_free(buf);
    else {
        buf = (char*)realloc(buf, (bytes + 5) * sizeof(char));
        buf[bytes] = '\0';
    }
    if (bytes >=1)
        buf[bytes - 1] = buf[bytes - 1] == '\n' ? '\0' : buf[bytes - 1];
    return buf;
}
