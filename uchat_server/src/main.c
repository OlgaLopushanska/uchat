#include "uchat_server.h"

 int main(int argc, char **argv) {
	t_serv *sr = mx_init_struct(NULL, argc, argv, 1);
	pthread_t listen_line = 0;

	if(argc >= 2) {
		fprintf(stdout, "uchat_server:: process id:  %d \n", getpid());
		mx_initial_database(sr);
		pthread_create(&listen_line, NULL, mx_listen_line, (void *)sr);
		while(1) 
			usleep(100000);
	}
	else {
		fprintf(stderr, "%s\n", "\033[31muchat_server:: wrong input data \033[0m");
		exit(1);
	}

}

