#ifndef CLIENT_HANDLER_H
#define CLIENT_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include<pthread.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>

#define SOCKETERROR (-1)
#define BUFSIZE 4096

void * handle_connection(void * arg);
int check(int exp, const char *msg);
int authenticate(const char *username, const char *password);

#endif

