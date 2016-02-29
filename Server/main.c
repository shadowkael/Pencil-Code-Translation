#include "userList.h"
#include "udpData.h"

pthread_mutex_t mutex;

void * UDP_thread(void * arg);
int main()
{
  puts("Server");

  int res;
  pthread_attr_t thread_attr;
  pthread_t udp_thread;

  if((res = pthread_attr_init(&thread_attr)) != 0)
    err_sys("thread attribute creation faliled");

  if((res = pthread_attr_setdetachstate(&thread_attr,
                                        PTHREAD_CREATE_DETACHED)) != 0)
    err_sys("setting detached attribute failed");

// Start UDP Server

  struct sockaddr_in serv, cli;
  char request[MSGSIZE];
  int sockfd, n, clilen;

  if((res = pthread_mutex_init(&mutex, NULL)) != 0)
    err_sys("pthread_mutex error");

  if((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) < 0)
    err_sys("UDP socket error");

  memset(&serv, 0, sizeof(serv));
  serv.sin_family = AF_INET;
  serv.sin_addr.s_addr = htonl(INADDR_ANY);
  serv.sin_port = htons(SERV_PORT);

  if(bind(sockfd, (SA)&serv, sizeof(serv)) < 0)
    err_sys("UDP bind error");

  clilen = sizeof(cli);
  for(;;){
      usleep(5000);
      pthread_mutex_lock(&mutex); // Using mutex to protect request[]
      UDP_DATA data;
      data.sockfd = sockfd;
      memset(request, 0, MSGSIZE);
      if((n = recvfrom(sockfd, request, MSGSIZE, 0,
                       (SA)&cli, (socklen_t*)&clilen)) < 0)
        continue;
      data.addr = cli;
      memcpy(data.msg, request, MSGSIZE);
      pthread_mutex_unlock(&mutex);

      // Create a new thread to manipulation data

      pthread_create(&udp_thread, &thread_attr, UDP_thread, (void*)&data);
    }
}

void * UDP_thread(void * arg){
  pthread_mutex_lock(&mutex);
  UDP_DATA data;
  memcpy(&data, (UDP_DATA*)arg, sizeof(UDP_DATA));
  pthread_mutex_unlock(&mutex);
  UL * to = NULL;
  int socklen = sizeof(struct sockaddr_in);
  char ack[33];
  char msg[MSGSIZE];
  time_t t;
  int flag = get_flag(data.msg);

  memset(ack, 0, ACKSIZE);
  memset(msg, 0, MSGSIZE);
  switch(flag){
    case MSG_LOGIN_REQ: // user login request
      if(ul_getuser(get_from(data.msg))){
          msg_create(ack, 0, 0, MSG_NAME_USED, NULL);
          sendto(data.sockfd, ack, ACKSIZE, 0, (SA)&data.addr, socklen);
        }else{
          time(&t);
          msg_create(ack, 0, 0, MSG_LOGIN_OK, NULL);
          sendto(data.sockfd, ack, ACKSIZE, 0, (SA)&data.addr, socklen);
          printf("LOGIN: %s(%s) %s", get_from(data.msg),
                 inet_ntoa(data.addr.sin_addr), ctime(&t));
          if(ul_LEN){
              memset(ack, 0, ACKSIZE);
              msg_create(ack, 0, get_from(data.msg), MSG_ONLINE, NULL);
              ul_online(data.sockfd, ack);
              msg_create(msg, 0, 0, MSG_USERLIST, NULL);
              ul_ltot(get_text(msg));
              sendto(data.sockfd, msg, MSGSIZE, 0, (SA)&data.addr, socklen);
            }else if(ul_LEN >= TEXTSIZE / UIDSIZE){
              memset(ack, 0, ACKSIZE);
              msg_create(ack, 0, 0, MSG_SERVFULL, NULL);
              sendto(data.sockfd, ack, ACKSIZE, 0, (SA)&data.addr, socklen);
            }
          ul_add(get_from(data.msg), &data.addr);
        }
      break;
    case MSG_TEXT:    // text message, DataFowarding
      time(&t);
      to = ul_getuser(get_to(data.msg));
      if(!ul_getuser(get_from(data.msg)) || !to)
        break;

      msg_create(msg, 0, get_from(data.msg), MSG_TEXT, get_text(data.msg));
      sendto(data.sockfd, msg, MSGSIZE, 0, (SA)&to->addr, socklen);
      msg_create(ack, 0, 0, MSG_SERVACK, NULL);
      sendto(data.sockfd, ack, ACKSIZE, 0, (SA)&data.addr, socklen);
      printf("%s > %s %s", get_from(msg), to->uid, ctime(&t));
      break;
    case MSG_QUIT:
      time(&t);
      if(!ul_getuser(get_from(data.msg)) || !ul_LEN)
        break;
      ul_del(get_from(data.msg));
      msg_create(ack, 0, get_from(data.msg), MSG_OFFLINE, NULL);
      ul_offline(data.sockfd, ack);
      printf("Quit: %s(%s) %s", get_from(data.msg),
             inet_ntoa(data.addr.sin_addr), ctime(&t));
      break;
    default:
      break;
  }
  pthread_exit(NULL);
}
