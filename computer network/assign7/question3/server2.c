#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/ipc.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<netdb.h>
#include<string.h>
int main(int argc,char* argv[])
{
int socfd,nsfd,portno;
socklen_t size;
socfd=socket(AF_INET,SOCK_STREAM,0);
if(socfd==-1)
{printf("error opeing socket\n");exit(0);}
if(argc<2)
{
    printf("argument error");exit(0);
}
struct sockaddr_in cliaddr,seraddr;
printf("seela");
char buf[100];
portno=atoi(argv[1]);
bzero((char*)&seraddr,sizeof(seraddr));
seraddr.sin_family=AF_INET;
seraddr.sin_addr.s_addr = htonl(INADDR_ANY);
seraddr.sin_port = htons(portno);
if (bind(socfd, (struct sockaddr *) &seraddr,
              sizeof(seraddr)) < 0)
             { printf("ERROR on binding\n");exit(0);}
     listen(socfd,5);
size=sizeof(cliaddr);
nsfd=accept(socfd,(struct sockaddr *) &cliaddr,&size);
while(1)
{
printf("server is waiting\n");



memset(buf,0,100);
recv(nsfd,buf,100,0);
printf("client said\t %s\n",buf);
memset(buf,0,100);
printf("to client\t");
gets(buf);
send(nsfd,buf,100,0);



}

return 0;
}

