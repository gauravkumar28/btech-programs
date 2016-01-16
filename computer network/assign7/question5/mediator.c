#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<netdb.h>
#include<netinet/in.h>
#include<pthread.h>
#include<poll.h>
#include<errno.h>



char buf[100];
char sserver[5][100];

void* chat(void *arg)
{
int asfd;
struct pollfd pfd[2];
int id=(*(int*)arg);
printf("%d\n",id);
asfd=socket(AF_INET,SOCK_STREAM,0);
struct sockaddr_in mediator2;
bzero(&mediator2,sizeof(mediator2));
mediator2.sin_family=AF_INET;
mediator2.sin_addr.s_addr=inet_addr("127.0.0.1");
mediator2.sin_port=htons(atoi(buf));
if(connect(asfd,(struct sockaddr *)&mediator2,sizeof(mediator2))==-1)
{perror("error in connection");exit(1);}
//send(asfd,"hi",strlen("hi"),0);

pfd[0].fd=asfd;
pfd[1].fd=id;
pfd[0].events=POLLIN;
pfd[1].events=POLLIN;
while(1)
{

int p=poll(pfd,2,1000);
if(p>0)
{
printf("vaibahv\n");
if(pfd[0].revents&POLLIN)
{printf("ram\n");
memset(buf,0,100);
recv(asfd,buf,100,0);
printf("recieved%s\n",buf);
send(id,buf,100,0);

}
else if(pfd[1].revents&POLLIN)
{
memset(buf,0,100);
recv(id,buf,100,0);
printf("recieved\n");
send(asfd,buf,100,0);

}}
}}



int main()
{
strcpy(sserver[0],"1000");
strcpy(sserver[1],"1100");
strcpy(sserver[2],"1200");
strcpy(sserver[3],"1300");
strcpy(sserver[4],"1400");
int sfd,nsfd,clientsize;
sfd=socket(AF_INET,SOCK_STREAM,0);
if(sfd==-1)
{printf("sock error");
exit(1);
}

struct sockaddr_in mediator1,client;
bzero((char*)&mediator1,sizeof(mediator1));

mediator1.sin_family=AF_INET;
mediator1.sin_port=htons(2500);
mediator1.sin_addr.s_addr=INADDR_ANY;

if(bind(sfd,(struct sockaddr *)&mediator1,sizeof(mediator1))==-1)
{perror("bind error");exit(1);}

listen(sfd,5);
clientsize=sizeof(client);
nsfd=accept(sfd,(struct sockaddr *)&client,&clientsize);
if(nsfd==-1)
{
perror("accept error");exit(1);}

memset(buf,0,100);
recv(nsfd,buf,100,0);
printf("%s\n",buf);
int i;
for(i=0;i<5;i++)
{
if(strcmp(buf,sserver[i])==0)
break;

}
if(i==5)
{
printf("spacial server not register\n");
}
else
{
pthread_t t;

pthread_create(&t,NULL,&chat,(void*)&nsfd);


pthread_join(t,NULL);

}

return 0;
}
