#include "client.h"

using namespace std;

int main(int argc, char * argv[])
{
    int sockfd, recvbytes;  
    char buf[MAXDATASIZE];  
    struct hostent *host;  
    struct sockaddr_in serv_addr;  
  
    if (( sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {  
        perror("socket error!");  
        exit(1);  
    }  
    bzero(&serv_addr,sizeof(serv_addr));  
    serv_addr.sin_family    = AF_INET;  
    serv_addr.sin_port      = htons(SERVPORT);  
    serv_addr.sin_addr.s_addr= inet_addr(SERVER_IP);  
  
    if (connect(sockfd, (struct sockaddr *)&serv_addr,sizeof(struct sockaddr)) == -1) {  
        perror("connect error!");  
        exit(1);  
    }  
  
    write(sockfd,DATA, sizeof(DATA));  
   if ((recvbytes = recv(sockfd, buf, MAXDATASIZE,0)) == -1) {  
        perror("recv error!");  
        exit(1);  
    }  
  
    buf[recvbytes] = '\0';  
    printf("Received: %s",buf);  
    close(sockfd);  
}  
