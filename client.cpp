#include "client.h"

#define SERVPORT 3333  
#define MAXDATASIZE 100  
#define SERVER_IP "127.0.0.1"  
#define DATA  "this is a client message"

#define BACKLOG 10

using namespace std;

void con_serv()                //connect and confirm with server
{
    int sockfd, recvbytes;  
    char buf[MAXDATASIZE];  
    struct hostent *host;  
    struct sockaddr_in serv_addr;  
  
    if (( sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {  
        perror("socket error!");  
        exit(1);  
    }  
    memset(&serv_addr, 0, sizeof(sockaddr_in));  
    serv_addr.sin_family    = AF_INET;  
    serv_addr.sin_port      = htons(SERVPORT);  
    serv_addr.sin_addr.s_addr= inet_addr(SERVER_IP);  
  
    if (connect(sockfd, (struct sockaddr *)&serv_addr,sizeof(struct sockaddr)) == -1) {  
        perror("connect error!");  
        exit(1);  
    }  
  
    write(sockfd, DATA, sizeof(DATA));  
    if ((recvbytes = recv(sockfd, buf, MAXDATASIZE,0)) == -1) {  
        perror("recv error!");  
        exit(1);
    }  
  
    buf[recvbytes] = '\0';  
    if(strcmp(buf,"connected!"))
    {
        cout<<"connected failed!"<<endl;
	exit(1);
    }
    printf("Received: %s\n",buf);  

    /*while(true)                    //需要将里面改成心跳服务  不需要了
    {
        int sin_size = sizeof(struct sockaddr_in);
        if((client_fd = accept(sockfd, (struct sockaddr*) &remote_addr, (socklen_t*)&sin_size)) == -1)
        {
            perror("accept error!");
            continue;
        }
        printf("Received a connection from %s\n",(char *)inet_ntoa(remote_addr.sin_addr));

        if(send(client_fd, msg, strlen(msg),0) == -1)
        {
            perror("send error!");
            close(client_fd);
            continue;
        }
    }*/
}  

void processing(char * buf)
{
    //process
    cout<<buf<<endl;
    con_serv();
}

int main(int argc, char * argv[])
{
    con_serv();

    int recvbytes;
    char * confirm = "wait recv";
    char * recv_error = "error";
    char buf[MAXDATASIZE];
    int PORT = 23333;
    int sockfd, client_fd;
    struct sockaddr_in my_addr;
    struct sockaddr_in remote_addr;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("recv socket create failed!");
        exit(1);
    }

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(PORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
//    bzero(&(my_addr.sin_zero),8);
    memset(&my_addr.sin_zero, 0, sizeof(my_addr.sin_zero));
    if(bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("recv bind error!");
        exit(1);
    }
    if(listen(sockfd, BACKLOG) == -1)
    {
        perror("recv listen error!");
        exit(1);
    }
    
    while(true)
    {
        int sin_size = sizeof(struct sockaddr_in);
        if((client_fd = accept(sockfd, (struct sockaddr*) &remote_addr, (socklen_t*)&sin_size)) == -1)
        {
            perror("recv accept error!");
            con_serv();
            continue;
        }
        if(send(client_fd, confirm, strlen(confirm), 0) == -1)
        {
            perror("recv send error!");
            close(client_fd);
            con_serv();
            continue;
        }
        memset(buf, 0, strlen(buf));
        if ((recvbytes = recv(sockfd, buf, MAXDATASIZE,0)) == -1)
        {
            perror("recv error!");
            close(client_fd);
            con_serv();
            continue;
        }
        processing(buf);
    }
}



















