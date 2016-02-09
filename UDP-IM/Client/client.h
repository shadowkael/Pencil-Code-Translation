#ifndef MY_ERR_H
#define MY_ERR_H

#endif // MY_ERR_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <myerr.h>
#include <pthread.h>
#include <time.h>
#include <locale.h>

#define SERV_PORT 8888

#define SA struct sockaddr *

int sockfd;
