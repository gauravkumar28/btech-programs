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


int flag=0;
char mainbuf[100];
pthread_mutex_t lock;
pthread_cond_t done;

int count=0;

void *fun(void *arg)

{int x=*(int*)arg;
printf("%d\n",x);
char buf[100];
int sfd,nsfd,sizeclient;

struct sockaddr_in server,client;
sfd=socket(AF_INET,SOCK_STREAM,0);
bzero((char*)&server,sizeof(server));
server.sin_family=AF_INET;
int a=inet_addr("127.0.0.10");
a=a+x;
printf("%d\n",a);
server.sin_addr.s_addr=a;
server.sin_port=htons(2500);

if((bind(sfd,(struct sockaddr *)&server,sizeof(server)))==-1)
{perror("bind error\n");exit(1);}
listen(sfd,5);

printf("rajesh\n");
sizeclient=sizeof(client);
nsfd=accept(sfd,(struct sockaddr*)&client,&sizeclient);
printf("%d\n",nsfd);
while(1)
{
if(nsfd==-1)
{
printf("error");exit(1);}
printf("++++++++\n");
memset(buf,0,100);
recv(nsfd,buf,100,0);
pthread_mutex_lock(&lock);
pthread_cond_wait(&lock,&done);
strcpy(mainbuf,buf);
pthread_cond_signal(&done);
printf("%s\n",buf);
printf("msg to client\n");
memset(buf,0,100);
gets(buf);
send(nsfd,buf,100,0);
pthread_mutex_unlock(&lock);
}
}
int main()
{
pthread_mutex_init(&lock,NULL);
pthread_cond_init(&done,NULL);
int i,c;
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
pthread_mutex_lock(&lock);
pthread_cond_wait(&lock,&done);
printf("in main thread%s\n",mainbuf);
pthread_cond_signal(&done);
pthread_mutex_unlock(&lock);
}

//printf("---------------sita\n");

}


*/

}
