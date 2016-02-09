#ifndef MY_ERR_H
#define MY_ERR_H

#endif // MY_ERR_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <myerr.h>
#include <pthread.h>
#include <time.h>
#define ACKSIZE   33
#define MSGSIZE  512
#define UIDSIZE   16
#define TEXTSIZE 478

#define SERV_PORT 8888

#define SA struct sockaddr *
