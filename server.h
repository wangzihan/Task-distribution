#include "pthread.h"
#include "sys/types.h"
#include "sys/socket.h"
#include "stdio.h"
#include "stdlib.h"
#include "errno.h"
#include "string.h"
#include "string"
#include "netinet/in.h"
#include "sys/wait.h"
#include "arpa/inet.h"
#include "list"
#include "log.h"

struct module
{
    std::string ip;
    int port;
};
