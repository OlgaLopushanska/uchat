#include "uchat_server.h"

void *mx_reciever(void *data){
    t_user *usr = (t_user*)data;
    char *rcv = NULL;
    pthread_t j;
    //int numbytes = 0;

    while (1) {
        rcv = mx_rec_edited(usr->cfd);
        if(!rcv && usr->ext == 0) {
            //fprintf(stderr, "\033[31muchat_server:: error reciving message - socket \"%d\"\033[0m\n", usr->cfd);//не удалось соедінітся с сокетом
            usr->ext = 1;
        }
        else if(usr->ext == 0)
            while(1) {
                pthread_mutex_lock(&(usr->Lock));
                if (!(usr->rcv)) {
                    usr->rcv = mx_strdup(rcv);
                    rcv = mx_free(rcv);
                    pthread_mutex_unlock(&(usr->Lock));
                    pthread_create(&j, NULL, mx_process_request, (void *)usr);
                    break;
                }
                pthread_mutex_unlock(&(usr->Lock));
                usleep(10000);
            }
        usleep(10000);

    }
    return 0;
}
