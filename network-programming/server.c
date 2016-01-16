#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
int main()
{
int sfd,nsfd,length;
char buf[100];
sfd=socket(AF_INET,SOCK_STREAM,0);
if(sfd==-1)
{

printf("\n socket  error  \n");
exit(1);

}

struct sockaddr_in  server , client;

bzero((char*)&server,sizeof(server));
server.sin_family=AF_INET;
server.sin_addr.s_addr=INADDR_ANY;
server.sin_port=htons(1500);

if(bind(sfd,(struct sockaddr *)&server,sizeof(server))==-1)
{
printf("bind error \n");
exit(1);

}
listen(sfd,5);


if((nsfd=accept(sfd,(struct sockaddr *)&server,&length))==-1)
{
printf("accept  error\n");
exit(1);
}
//while(1)

{

recv(nsfd,buf,100,0);
printf(" client said %s \n",buf);
memset(buf,0,100);
recv(nsfd,buf,100,0);
printf(" client said %s \n",buf);
memset(buf,0,100);
}
}
