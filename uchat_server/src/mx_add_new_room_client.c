#include "uchat_server.h"

void mx_add_new_room_client(t_req *req, t_user *usr) {
    char *message = NULL;
    char *num = NULL;
    char *user = NULL;
    char *room = NULL;
    char *id_room = NULL;

    user = mx_str_get_sub(&(req->req), 0, ':');
    room = mx_str_get_sub(&(req->req), 0, ':');
    num = mx_get_current_num();
    asprintf(&id_room, "%s_%s_%s", room, user, num);
    mx_add_new_room(user, room, id_room, usr);
    message = mx_send_rooms(user, usr);
    mx_send_message(req->num, "5", message, usr);
    user = mx_free(user);
    num = mx_free(num);
    room = mx_free(room);
    id_room = mx_free(user);
    message = mx_free(message);
}
