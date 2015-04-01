#include "server.h"
#include "unistd.h"

#define BACKLOG 10
#define MAXSIZE 1024

using namespace std;

void * add_module(void * args)
{
    /*log * msg = new log();

    int SERVPORT = 3333;
    cout<<"please input port(default 3333):";
    int tmp = 0;
    cin>>tmp;
    if(tmp > 0)SERVPORT = tmp;
    cout<<SERVPORT<<endl;

    //msg->common("server port set ");*/

    int SERVPORT = 3333;
    int sockfd, client_fd;
    struct sockaddr_in my_addr;
    struct sockaddr_in remote_addr;

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("add_modulesocket create failed!");
	exit(1);
    }

    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(SERVPORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
//    bzero(&(my_addr.sin_zero),8);
    memset(&my_addr.sin_zero, 0, sizeof(my_addr.sin_zero));
    if(bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1)
    {
        perror("add_module bind error!");
	exit(1);
    }
    if(listen(sockfd, BACKLOG) == -1)
    {
        perror("add_modulelisten error!");
	exit(1);
    }

    while(true)
    {
        int sin_size = sizeof(struct sockaddr_in);
	if((client_fd = accept(sockfd, (struct sockaddr*) &remote_addr, (socklen_t*)&sin_size)) == -1)
	{
            perror("accept error!");
	    continue;
	}
	printf("Received a connection from %s\n",(char *)inet_ntoa(remote_addr.sin_addr));
        char * msg = "connected!";
        if(send(client_fd, msg, strlen(msg),0) == -1)
        {
            perror("send error!");
            close(client_fd);
            continue;
        }
       
        list<module*> * mods = (list<module*>*)args;          //将新连接上的客户端添加进mods
        module * tmp = new module();
        tmp->ip = inet_ntoa(remote_addr.sin_addr);
        tmp->port = remote_addr.sin_port;
        mods->push_back(tmp);

        cout<<tmp->ip<<" "<<tmp->port<<endl;

        list<module*>::iterator i = mods->begin();
        cout<<(*i)->ip<<endl;
        cout<<(*i)->port<<endl;
        cout<<mods->size()<<endl;

	/*if(!fork())
	{
	    int rval;
	    char buf[MAXSIZE];
	    if((rval = read(client_fd, buf, MAXSIZE)) < 0)
	    {
	        perror("reading stream error!");
		continue;
	    }

	    char * msg = "connected!";
	    if(send(client_fd, msg, strlen(msg),0) == -1)
	        perror("send error!");
	    close(client_fd);
	    exit(0);
	}
	close(client_fd);*/
    }
}

int main(int argc, char * argv[])
{
    pthread_t addtid;
    int err;
    list<module*> mods;
    if((err = pthread_create(&addtid, NULL, add_module, (void *)&mods)) != 0)
    {
        perror("connect server error!");
        exit(1);
    }
    
    sleep(10);
    list<module*>::iterator i = mods.begin();
    cout<<(*i)->ip<<endl;
    cout<<(*i)->port<<endl;
    cout<<mods.size()<<endl;
}
