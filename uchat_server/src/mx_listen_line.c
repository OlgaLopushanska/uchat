#include "uchat_server.h"
#include <ctype.h>

void *mx_listen_line(void *data){
    t_serv *sr = (t_serv*)data;
    t_user *usr = NULL;

    char *sql_in = NULL;
    //char *temp = NULL;
    char *err_msg = NULL;

    int port = mx_atoi(sr->argv[1]);
	struct sockaddr_in svaddr, claddr;
	int cfd;
	socklen_t len;
	int size_claddr = 0;
	int backlog = 5;
	int rc = 1;
	pthread_t j = 0;
	
    printf("%s\033[0m\n", "\033[0muchat_server:: trying create connection");
    while((sr->sfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
        fprintf(stderr, "%s\n", "\033[31muchat_server:: fault create connection \033[0m");
        exit(1);
	}
	mx_memset(&svaddr, 0, sizeof(struct sockaddr_in));
	svaddr.sin_family = AF_INET;
	svaddr.sin_addr.s_addr = INADDR_ANY;
	svaddr.sin_port = htons(port); //можна
	setsockopt(sr->sfd, SOL_SOCKET, SO_REUSEADDR, (char *)&rc, sizeof(int));
	if (bind(sr->sfd, (struct sockaddr *) &svaddr, sizeof(struct sockaddr_in)) == -1)
        fprintf(stderr, "%s\n", "\033[31muchat_server:: bind error \033[0m");
	if (listen(sr->sfd, backlog) == -1)
        fprintf(stderr, "%s\n", "\033[31muchat_server:: listen error \033[0m");//не удалось соедінітся с сокетом
	size_claddr = sizeof(claddr);
    printf("%s\033[0m\n", "\033[32muchat_server:: connection is created");
	for (; ; ) {
		len = sizeof(struct sockaddr_in);
		cfd = accept(sr->sfd, (struct sockaddr *) &claddr, (socklen_t *)&size_claddr); //создаем новий  сокет слушающий
		if (cfd == -1){
            fprintf(stderr, "%s\n", "\033[31muchat_server:: fault create socket \033[0m");
		}
		else{
			printf("%s %d\033[0m\n", "\033[32muchat_server:: user has connected, session: ", cfd);
            sql_in = sql_in ? (char*)mx_free(sql_in) : NULL;

            asprintf(&sql_in, "INSERT INTO Connect(Login, User_Id, Socket, Pr1) VALUES ('-1',0,%d,0);", cfd);
            rc = sqlite3_exec(sr->db_c, sql_in, 0, 0, &err_msg);
            if(rc == SQLITE_OK){
                usr = mx_init_struct_user(NULL, sr, cfd, 1);
                usr->con_id =  sqlite3_last_insert_rowid(sr->db_c);
                pthread_create(&j, NULL, mx_new_connection, (void *)usr);
                sql_in = sql_in ? (char*)mx_free(sql_in) : NULL;
            }
        }
	}
    return 0;

}

