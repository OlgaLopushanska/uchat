#ifndef UCHAT_H
#define UCHAT_H

#include <gtk/gtk.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <sqlite3.h>
#include <sys/time.h>

typedef struct s_serv {
    int argc;
    char **argv;
    int sfd;
    sqlite3 *db_c, *db_u, *db_r, *db_h, *db_ur;
    pthread_mutex_t Lock;
    int n_st_room;
    char **rooms;
    char **id_rooms;

} t_serv;

typedef struct s_user {
    t_serv *sr;
    int cfd;
    int con_id;
    pthread_mutex_t Lock;
    char *snd, *rcv;
    int ext;
   	pthread_t sender, reciever, run;

} t_user;

typedef struct s_req {
    char *message;
    char *num;
    int type;
    char *req;
} t_req;

typedef struct s_db {
    int par1, par2, par3;
    char *cpar1;
    int n_row;
    int argc;
    char ***cpar3;
    char *what_find;
    sqlite3 *db;
} t_db;

#define SEND_BUFF_SIZE 1025
#define SERVER_PORT 5000

typedef struct s_client {
    int sockld;
    struct sockaddr_in serv_addr;
} t_client;



void mx_headband(GtkApplication* app, gpointer data);
void mx_register(GtkApplication* app, gpointer data);
bool mx_valid(const char *s, int n);
void mx_account(gpointer data);
void mx_enter(GtkApplication* app, gpointer data);
void mx_chat_main(GtkApplication* app, gpointer data);
bool mx_make_request(gpointer data, int n);
char *mx_client(gpointer data, char *u, int n);
void mx_initial_database(t_serv *sr);
void *mx_listen_line(void *data);
t_serv *mx_init_struct(t_serv *srv, int argc, char **argv, int par);
void *mx_new_connection(void *data);
void *mx_sender(void *data);
void *mx_reciever(void *data);
void mx_send_message(char* num_msg, char* type, char *msg, t_user *usr);
char *mx_recive_message(char *num, t_user *usr);
void *mx_free(void *arr);
void **mx_free2(void **arr, int a);
char *mx_rec_edited(const int fd);
void *mx_process_request(void *data);
void mx_process_request2(t_req *req, t_user *usr);
void mx_add_new_user(t_req *req, t_user *usr);
int mx_find_in_db(void *data, int argc, char **argv, char **colName);
t_db *mx_find_id(char *table, char* colum, char *value, t_db *tdb);
void mx_db_send_req(sqlite3 *db, char *sql_req,
                    int (*func)(void *, int , char **, char **), t_db *tdb);
t_db *mx_int_struct_tdb(t_db *tdb, int par);
t_user *mx_init_struct_user(t_user *usr, t_serv *sr, int cfd, int par);
void mx_enter_user(t_req *req, t_user *usr);
char *mx_str_get_sub (char **in, const char s1, const char s2);
void mx_change_name(t_req *req, t_user *usr);
char *mx_get_current_num();
void mx_add_new_room(char *user, char *room, char *id_room, t_user *usr);
void mx_add_user_to_room(char *new_user, char *room, char *id_room, t_user *usr);
int mx_get_data(void *data, int argc, char **argv, char **colName);
t_db *mx_find_id(char *table, char* colum, char *value, t_db *tdb);
void mx_send_users(t_req *req, t_user *usr);
char *mx_users_get_list(char *id_room, t_user *usr);
char* mx_send_rooms(char *user, t_user *usr);
void mx_add_new_room_client(t_req *req, t_user *usr);
void mx_add_user_to_room_c(t_req *req, t_user *usr);
void mx_del_user_fr_room(t_req *req, t_user *usr);
void mx_del_room(t_req *req, t_user *usr);
void mx_recive_text(t_req *req, t_user *usr);
void mx_send_to_users(char *id_room, char *message, t_user *usr);
void mx_send_all_history(t_req *req, t_user *usr);
void mx_del_account(t_req *req, t_user *usr);

//libmx
int mx_strcmp(const char *s1, const char *s2);
bool mx_isdigit(int c);
bool mx_isalpha(int c);
int mx_strlen(const char *s);
char *mx_strcpy(char *dst, const char *src);
char *mx_strjoin(const char *s1, const char *s2);
char *mx_strnew(const int size);
void *mx_memset(void *b, int c, size_t len);
double mx_pow(double n, unsigned int pow);
int mx_atoi(char *str);
char *mx_strncpy(char *dst, const char *src, int len);
char *mx_strndup(const char *s1, size_t n);
char *mx_strdup(const char *s1);
char *mx_itoa(int number);
char *mx_strcpy(char *dst, const char *src);
int mx_get_substr_index(const char *str, const char *sub);
char *mx_strnew(const int size);
void *mx_memrchr(const void *s, int c, size_t n);
void *mx_memchr(const void *s, int c, size_t n);
int mx_get_char_index(const char *str, char c);

#endif
