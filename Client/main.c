#include "client.h"
#include "win.h"

char msgtmp[MSGSIZE]; // message waiting for ack
char uid[UIDSIZE];
pthread_mutex_t mutex; // protect msgtmp[]

void * msg_thread_fn(void *arg);
int main(){
  int i, c, res;
  struct sockaddr_in serv;
  char text[TEXTSIZE], msg[MSGSIZE];
  pthread_attr_t thread_attr;
  pthread_t msg_thread;
  ITEM * cur_item = NULL;
  void (*p)(char*);

  if((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    err_sys("socket error");
  bzero(&serv, sizeof(serv));
  serv.sin_family = AF_INET;
  serv.sin_addr.s_addr = inet_addr(SERV_ADDR);
  serv.sin_port = htons(SERV_PORT);
  // Login
  printf("Client start ...\n");
  while(uid[0] == '\n' || uid[0] == '\0'){
      printf("input your ID: ");
      fgets(uid, UIDSIZE + 1, stdin);
    }
  uid[strlen(uid) - 1] = '\0';
  bzero(msg, MSGSIZE);
  msg_create(msg, 0, uid, MSG_LOGIN_REQ, NULL);
  if(sendto(sockfd, msg, MSGSIZE, 0, (SA)&serv, sizeof(serv)) != MSGSIZE)
    err_sys("sendto error");
  bzero(msg, MSGSIZE);
  if(recvfrom(sockfd, msg, MSGSIZE, 0, (SA)NULL, (socklen_t*)NULL) < 0)
    err_sys("login failed");
  if(get_flag(msg) == MSG_NAME_USED)
    err_quit("this ID has been used");
  else if(get_flag(msg) == MSG_SERVFULL)
    err_quit("Server is full");

  setlocale(LC_ALL, "");
  init_window();
  uid_show(uid);

  // start a new thread for received data
  if((res = pthread_attr_init(&thread_attr)) != 0)
    err_sys("thread attribute creation faliled");
  if((res = pthread_attr_setdetachstate(&thread_attr,
                                        PTHREAD_CREATE_DETACHED)) != 0)
    err_sys("setting detached attribute failed");
  pthread_mutex_init(&mutex, NULL);
  pthread_create(&msg_thread, &thread_attr, msg_thread_fn, (void*)&serv);

  // process input characters
  i = 0;
  bzero(text, TEXTSIZE);
  for(;;){
      c = getch();
      switch(c){
        case '\r':case '\n':
          bzero(msg, MSGSIZE);
          msg_create(msg, now_user, uid, MSG_TEXT, text);
          sendto(sockfd, msg, MSGSIZE, 0, (SA)&serv, sizeof(serv));

          pthread_mutex_lock(&mutex);
          strcpy(msgtmp, get_text(msg));
          pthread_mutex_unlock(&mutex);
          memset(text, ' ', TEXTSIZE);
          mvwprintw(win_text, 1, 1, "%s", text);
          bzero(text, TEXTSIZE);
          i = 0;
          wrefresh(win_text);
          break;
        case KEY_UP:case KEY_LEFT:
          if(!n_users) break;
          menu_driver(user_list, REQ_UP_ITEM);
          cur_item = current_item(user_list);
          p = item_userptr(cur_item);
          p((char*)item_name(cur_item));
          wrefresh(box_users);
          break;
        case KEY_DOWN:case KEY_RIGHT:
          if(!n_users) break;
          menu_driver(user_list, REQ_DOWN_ITEM);
          cur_item = current_item(user_list);
          p = item_userptr(cur_item);
          p((char*)item_name(cur_item));
          wrefresh(box_users);
          break;
        case KEY_BACKSPACE:
          if(i > 0)
            text[--i] = '\0';
          wclear(win_text);
          waddstr(win_text, text);
          wrefresh(win_text);
          break;
        case 3: // process Ctrl-C
          bzero(msg, MSGSIZE);
          msg_create(msg, 0, uid, MSG_QUIT, NULL);
          sendto(sockfd, msg, MSGSIZE, 0, (SA)&serv, sizeof(serv));
          win_exit();
          break;
        default:
          if(i >= TEXTSIZE)
            break;
          text[i++] = c;
          wclear(win_text);
          waddstr(win_text, text);
          wrefresh(win_text);
        }
    }

  endwin();
}

void * msg_thread_fn(void * arg){
  time_t t;
  int flag;
  char msg[MSGSIZE];
  struct sockaddr_in serv;
  memcpy(&serv, (struct sockaddr_in*)arg, sizeof(serv));

  for(;;){
      bzero(msg, MSGSIZE);
      if(recvfrom(sockfd, msg, MSGSIZE, 0, (SA)NULL, (socklen_t*)NULL) < 0)
        continue;
      flag = get_flag(msg);

      switch(flag){
        case MSG_USERLIST:
          ttolist(get_text(msg));
          user_list_show();
          ITEM *cur;
          void (*p)(char *);
          cur = current_item(user_list);
          p = item_userptr(cur);
          p((char *)item_name(cur));
          break;
        case MSG_SERVACK:
          time(&t);
          wprintw(win_msg, "-> %s---%s", now_user, ctime(&t));
          pthread_mutex_lock(&mutex);
          wprintw(win_msg, "%s\n", msgtmp);
          pthread_mutex_unlock(&mutex);
          wrefresh(win_msg);
          break;
        case MSG_TEXT:
          time(&t);
          wprintw(win_msg, "%s---%s", get_from(msg), ctime(&t));
          wprintw(win_msg, "%s\n", get_text(msg));
          wrefresh(win_msg);
          break;
        case MSG_OFFLINE:
          uoffline(get_from(msg));
          user_list_show();
          break;
        case MSG_ONLINE:
          strcpy(users[n_users++], get_from(msg));
          user_list_show();
          break;
        default:
          break;
        }
    }
}
