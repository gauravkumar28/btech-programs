#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<netdb.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>

int sfd;
int flag=0;
char mainbuf[100];

int count=0;

void *fun(void *arg)

{
char buf[100];
int nsfd,sizeclient;
struct sockaddr_in client;

sizeclient=sizeof(client);
nsfd=accept(sfd,(struct sockaddr*)&client,&sizeclient);
while(1)
{
if(nsfd==-1)
{
printf("error");exit(1);}
memset(buf,0,100);
recv(nsfd,buf,100,0);
strcpy(mainbuf,buf);
flag=1;
printf("%s\n",buf);
printf("msg to client\n");
memset(buf,0,100);
gets(buf);
send(nsfd,buf,100,0);

}
}
int main()
{
int i,c;
struct sockaddr_in server;
sfd=socket(AF_INET,SOCK_STREAM,0);
bzero((char*)&server,sizeof(server));
server.sin_family=AF_INET;
server.sin_addr.s_addr=INADDR_ANY;
server.sin_port=htons(2500);
if((bind(sfd,(struct sockaddr *)&server,sizeof(server)))==-1)
{perror("bind error\n");exit(1);}
listen(sfd,5);

for(i=0;i<10;i++)
{
c=fork();
if(c==0)
{
pthread_t p[10];
int j;
for(j=0;j<10;j++)
{
pthread_create(&p[j],NULL,&fun,&count);count=count+10;}

for(j=0;j<10;j++)
pthread_join(p[j],NULL);
}

}


while(1)
{
if(flag==1)
{printf("sita\n");
printf("in main thread%s\n",mainbuf);flag=0;}

}

//printf("---------------sita\n");



return 0;
}
