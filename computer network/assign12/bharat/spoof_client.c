#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/stat.h>
#include<signal.h>
#include<sys/sem.h>
#include<pthread.h>

int sfd;
struct sockaddr_in serv;
void* rcv()
{
	struct sockaddr_in clt;
	int length;
char buf[512];
while(1)
{
recvfrom(sfd,buf,512,0,(struct sockaddr*)&clt,&length);
printf("received msg is:%s\n",buf);
}
}

int main()
{
sfd=socket(AF_INET,SOCK_DGRAM,0);
struct sockaddr_in myaddr;
myaddr.sin_family=AF_INET;
myaddr.sin_port=htons(3400);
myaddr.sin_addr.s_addr=INADDR_ANY;
int b=bind(sfd,(struct sockaddr*)&myaddr,sizeof(struct sockaddr_in));
if(b==-1)
perror("bind error\n"); 



serv.sin_family=AF_INET;
serv.sin_port=htons(2300);
inet_pton(AF_INET,"127.0.0.1",&serv.sin_addr);
pthread_t t;
pthread_create(&t,NULL,&rcv,NULL);
while(1)
{
char buf[512]={0};
fgets(buf,512,stdin);
sendto(sfd,buf,512,0,(struct sockaddr*)&serv,sizeof serv);
}
return 0;
}
