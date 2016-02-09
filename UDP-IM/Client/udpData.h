#ifndef UDPDATA_H
#define UDPDATA_H

#endif // UDPDATA_H

#define ACKSIZE 33
#define MSGSIZE 512
#define UIDSIZE 16
#define TEXTSIZE 478

#define MSG_TEXT       0
#define MSG_LOGIN_OK   1
#define MSG_ONLINE     2
#define MSG_NAME_USED  3
#define MSG_SERVACK    4
#define MSG_OFFLINE    5
#define MSG_USERLIST   6
#define MSG_SERVFULL   7
#define MSG_LOGIN_REQ 11
#define MSG_QUIT      17

//functions to manipulation message data

void msg_create(char * msg, const char * to, const char * from,
                int flag, const char * text){
  if(to) strcpy(msg, to);
  if(from) strcpy(msg + UIDSIZE, from);
  msg[UIDSIZE * 2] = flag;
  if(text) strcpy(msg + 33, text);
}

int get_flag(char * msg){
  return msg[UIDSIZE * 2];
}

char * get_to(char * msg){
  return msg;
}

char * get_from(char * msg){
  return(msg + UIDSIZE);
}

char * get_text(char * msg){
  return(msg + 33);
}
