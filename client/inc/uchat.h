#ifndef UCHAT_H
#define UCHAT_H

#include <gtk/gtk.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <pthread.h>
#include "./libxml2/inc/libmx.h"

 typedef struct s_user {
    GtkApplication *app;
    GtkWidget *euser;
    GtkWidget *epass;
    GtkWidget *epass2;
    GtkWidget *email;
    GtkWidget *sex1;
    GtkWidget *entry1;
    GtkWidget *entry2;
    GtkWidget *ap_entry1;
    GtkWidget *ap_entry2;
    GtkWidget *a_label4;
    GtkWidget *a_label6;
    GtkWidget *chat_label1;
    GtkWidget *chat_entry;
    GtkWidget *main_window;
    GtkWidget *e_window;
    GtkWidget *reg_window;
    GtkWidget *reg_right_wind;
    GtkWidget *a_window;
    GtkWidget *ap_window;
    GtkWidget *chat_window;
    GtkWidget *prof_image;
    GtkWidget **button;
    GtkWidget *box_rooms;
    GtkWidget *box_rooms2;
    GtkWidget *box_users;
    GtkWidget *box_users2;
    GtkWidget **user_row;
    GtkWidget **user_lable;
    GtkWidget *box4;
    GtkWidget *window_new_room;
    GtkWidget *entry_new_room;
    GtkWidget *button_new_room;
    GtkWidget *window_add_user;
    GtkWidget *entry_add_user;
    GtkWidget *button_add_user;
    GtkWidget *but_c_new_chat;
    GtkWidget *but_c_add_user;
    GtkWidget *box_chat1, *box_chat2;
    GtkWidget **msg;
    pthread_t connect;
    pthread_t sender;
    pthread_t resiever;
    char *user ;
    char *pass ;
    char *pass2 ;
    char *email1 ;
    char *sex;
    int fl;
    char *name;
    char *surname;
    char *current;
    int theme;
    int close;
    char **argv;
    int sfd;
    int f_exit;
    pthread_mutex_t Lock;
    int bufsize;
    char *snd, *rcv;
    int b_num_rooms;
    int c_room;
    int c_user;
    char ***rooms;
    int n_users;
    char **users;
    char *new_room;
    char *add_user;
    char *css_d;
    char *css_l;
    char *css3;
    char *css4;
    char **text;
    int n_t;
}   t_user;

typedef struct s_req {
    char *message;
    char *num;
    int type;
    char *req;
}   t_req;


typedef struct s_client {
    int sockld;
    struct sockaddr_in serv_addr;
}   t_client;

t_user *mx_struct_init(t_user *s);
void *mx_connect_to_server(void *data);
void *mx_sender(void *data);
void *mx_reciever(void *data);
t_user *mx_free_struct(t_user *s);
void *mx_free(void *arr);
void **mx_free2(void **arr, int a);
char *mx_rec_edited(const int fd);
t_req *mx_free_struct_req(t_req *req);
void *mx_process_request(void *data);
void mx_redraw_room(t_req *req, t_user *s);
t_req *mx_divide_req(t_req *req);
void mx_add_chat_line(t_req *req, t_user *s);
void mx_button_rooms_get(t_req *req, t_user *s, int par);
int mx_atoi(char *str);
char *mx_str_get_sub (char **in, const char s1, const char s2);
char *mx_line_resize(char *in, int size);
void mx_button_rooms(t_user *s, int par);
void mx_send_message(char* num_msg, char* type, char *msg, t_user *s);
void mx_list_box(t_user *s, int par);
void mx_change_users_list(t_req *req, t_user *s);
char *mx_get_current_num(void);
t_req *mx_recive_message(char *num, t_user *s);
void mx_get_all_history(t_user *s);
void *mx_run_interface(void *data);
void mx_headband(GtkApplication* app, gpointer data);
void mx_enter(GtkApplication *app, gpointer data);
void mx_register(GtkApplication* app, gpointer data);
bool mx_valid(const char *s, int n);
bool mx_add_new_user(t_user *s);
void mx_error_dialog(GtkWidget *button, gpointer *data, char *message);
void mx_account(gpointer data);
void mx_chat_main(GtkApplication* app, gpointer data);
GtkWidget *mx_create_scroll(GtkWidget *widg, int X, int Y, t_user *s);
void mx_add_room(GtkWidget *button, gpointer *data);
void mx_del_room(GtkWidget *button, gpointer data);
void mx_send_text_line(GtkWidget *button, gpointer data);
void mx_del_user_from_room(GtkWidget *button, gpointer data);
void mx_add_style(GtkWidget *widg, int type, t_user *s);
void mx_little_window(t_user *s);

#endif
