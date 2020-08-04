#include "uchat_server.h"

void *listen_port(void *data) {
	/*int numbytes = 0;
	int sfd = *(int*)data;
	int bufsize = 256;
	char buf[bufsize];
	int ext = 1;



	*/return 0;	
}


void *mx_new_connection(void *data) {
    t_user *usr = (t_user*)data;
    char *sql_in = NULL;
    int res = 0;
    char *err_msg = NULL;

    usr->ext = 0;

    pthread_create(&(usr->sender), NULL, mx_sender, (void *)usr);
    pthread_create(&(usr->reciever), NULL, mx_reciever, (void *)usr);

    while(1) {
        pthread_mutex_lock(&(usr->Lock));
        if(usr->ext) {
            pthread_cancel(usr->sender);
            pthread_cancel(usr->reciever);
            //delete usr;
            fprintf(stdout, "\033[33muchat_server:: connection %d is closed \033[0m\n", usr->cfd);//не удалось соедінітся с сокетом
            pthread_mutex_unlock(&(usr->Lock));
            asprintf(&sql_in, "DELETE FROM Connect WHERE Socket = %d;", usr->cfd);
            res = sqlite3_exec(usr->sr->db_c, sql_in, 0, 0, &err_msg);
            sql_in = mx_free(sql_in);
            if(res != SQLITE_OK)
                fprintf(stderr, "\033[31muchat_server:: connection %d - %s\033[0m\n", usr->cfd, sqlite3_errmsg(usr->sr->db_c));
            pthread_exit(NULL);
        }
        pthread_mutex_unlock(&(usr->Lock));
        usleep(10000);
    }

    return 0;
}
