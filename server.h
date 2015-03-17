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
#define BACKLOG 10
#define MAXSIZE 1024
