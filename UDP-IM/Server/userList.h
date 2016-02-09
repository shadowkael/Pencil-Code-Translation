#ifndef USERLIST_H
#define USERLIST_H

#endif // USERLIST_H

#include "server.h"

typedef struct user_list{
  char uid[16];
  struct sockaddr_in addr;
  struct user_list * next;
}UL;

UL * head = NULL;
int ul_LEN = 0;
// List functions

void ul_ltot(char * text){
  // list to text
  int i = 0;
  UL * htmp = head;

  while(htmp && i < TEXTSIZE - UIDSIZE){
      strcpy(text + i, htmp->uid);
      i += UIDSIZE;
      htmp = htmp->next;
    }
}

void ul_online(int sockfd, const char * ack){
  // tell all users that a new user is online
  UL * htmp = head;
  int socklen = sizeof(struct sockaddr_in);

  while(htmp){
      sendto(sockfd, ack, ACKSIZE, 0, (SA)&htmp->addr, socklen);
      htmp = htmp->next;
    }
}

void ul_offline(int sockfd, const char * ack){
  // tell all users that a user is offline
  UL * htmp = head;
  int socklen = sizeof(struct sockaddr_in);

  while(htmp){
    sendto(sockfd, ack, ACKSIZE, 0, (SA)&htmp->addr, socklen);
    htmp = htmp->next;
  }
}

UL * ul_getuser(const char * uid){
  UL * htmp;

  htmp = head;
  while(htmp){
      if(!strcmp(htmp->uid, uid))
          return htmp;
      htmp = htmp->next;
    }
  return NULL;
}

int ul_del(char * uid){
  UL * node = head, * htmp = head;

  if(!strcmp(htmp->uid, uid)){
      head = head->next;
      free(htmp);
      --ul_LEN;
      return 1;
    }else{
      htmp = htmp->next;
    }
  while(htmp){
      if(!strcmp(htmp->uid, uid)){
          node->next = htmp->next;
          free(htmp);
          --ul_LEN;
          return 1;
        }else{
          node = htmp;
          htmp = htmp->next;
        }
    }
  return 0;
}

int ul_add(const char * uid, struct sockaddr_in * addr){
  UL * htmp, *node;

  if(!(node = (UL*)malloc(sizeof(UL))))
    return 0;

  strcpy(node->uid, uid);
  memcpy(&node->addr, addr, sizeof(struct sockaddr_in));
  node->next = NULL;
  if(!head){
      head = node;
      ++ul_LEN;
      return 1;
    }
  htmp = head;
  while(htmp->next)
    htmp = htmp->next;
  htmp->next = node;
  ++ul_LEN;
  return 1;
}
