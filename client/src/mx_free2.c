#include "uchat.h"

void **mx_free2(void **arr, int a) {
    int i = 0;

    if (arr)
        for( ; i < a; i++)
            arr[i] = mx_free(arr[i]);
    arr = NULL;
    return arr;
}
