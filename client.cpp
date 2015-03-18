#include "client.h"

#define SERVPORT 3333  
#define MAXDATASIZE 100  
#define SERVER_IP "127.0.0.1"  
#define DATA  "this is a client message"

using namespace std;

bool con_serv()
{
    int sockfd, recvbytes;  
    char buf[MAXDATASIZE];  
    struct hostent *host;  
    struct sockaddr_in serv_addr;  
  
    if (( sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {  
        perror("socket error!");  
        return false;  
    }  
    memset(&serv_addr, 0, sizeof(sockaddr_in));  
    serv_addr.sin_family    = AF_INET;  
    serv_addr.sin_port      = htons(SERVPORT);  
    serv_addr.sin_addr.s_addr= inet_addr(SERVER_IP);  
  
    if (connect(sockfd, (struct sockaddr *)&serv_addr,sizeof(struct sockaddr)) == -1) {  
        perror("connect error!");  
        return false;  
    }  
  
    write(sockfd, DATA, sizeof(DATA));  
    if ((recvbytes = recv(sockfd, buf, MAXDATASIZE,0)) == -1) {  
        perror("recv error!");  
        return false;
    }  
  
    buf[recvbytes] = '\0';  
    if(strcmp(buf,"connected!"))
    {
        cout<<"connected failed!"<<endl;
	return false;
    }
    printf("Received: %s\n",buf);  
    close(sockfd);
    return true;
}  

int main(int argc, char * argv[])
{
    if(!con_serv())
    {
        perror("connect server error!");
	exit(1);
    }
    

}
