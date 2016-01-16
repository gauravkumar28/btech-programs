#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>


int main(int argc,char *argv[])
{
char buf[100];

int sfd,asfd,mediatorsize;
struct sockaddr_in sserver,mediator;
sfd=socket(AF_INET,SOCK_STREAM,0);
if(sfd==-1)
{printf("sock error\n");exit(1);}
bzero(&sserver,sizeof(sserver));
sserver.sin_family=AF_INET;
//int m=atoi(argv[1]);
//printf("port is %d\n",m);
sserver.sin_port=htons(atoi(argv[1]));
sserver.sin_addr.s_addr=INADDR_ANY;
printf("bharath\n");
if(bind(sfd,(struct sockaddr *)&sserver,sizeof(sserver))==-1)
{perror("bind");exit(1);}

listen(sfd,5);

mediatorsize=sizeof(mediator);
printf("ram\n");
asfd=accept(sfd,(struct sockaddr *)&mediator,&mediatorsize);
if(asfd==-1)
{
perror("aeecpt error");exit(1);}


while(1)
{
printf("replay\n");
memset(buf,0,100);
gets(buf);
if(send(asfd,buf,100,0)==-1)
{perror("send");exit(1);}
memset(buf,0,100);
recv(asfd,buf,100,0);
printf("%s\n",buf);

}
return 0;
}
