#include "pthread.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "stdio.h"
#include "stdlib.h"
#include "errno.h"
#include "string.h"
#include "netinet/in.h"
#include "sys/wait.h"
#include "arpa/inet.h"

#include "log.h"

#define SERVPORT 3333  
#define MAXDATASIZE 100  
#define SERVER_IP "127.0.0.1"  
#define DATA  "this is a client message"  
