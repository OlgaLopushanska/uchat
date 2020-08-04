#include "uchat_server.h"

void mx_process_request2(t_req *req, t_user *usr) {
    if(req->type == 1)  //create ne user
        mx_add_new_user(req, usr);
    if(req->type == 2) //enter user
        mx_enter_user(req, usr);
    if(req->type == 3) //change name
        mx_change_name(req, usr);
    if(req->type == 4) //send users list
        mx_send_users(req, usr);
    if(req->type == 5) //add new room
        mx_add_new_room_client(req, usr);
    if(req->type == 6) //add new user to room
        mx_add_user_to_room_c(req, usr);
    if(req->type == 7) //delete users from room
        mx_del_user_fr_room(req, usr);
    if(req->type == 8) //delete room
        mx_del_room(req, usr);
    if(req->type == 9) //get text
        mx_recive_text(req, usr);
    if(req->type == 10) //send hstory
        mx_send_all_history(req, usr);
    if(req->type == 11) //send hstory
        mx_send_all_history(req, usr);
     if(req->type == 12) //send hstory
        mx_del_account(req, usr);
   
}

