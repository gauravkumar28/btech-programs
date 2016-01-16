#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/select.h>
#include<sys/types.h>
#include<netdb.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<errno.h>

void *tcp_service(void *arg)//thread for tcp service
{
	printf("thread\n");
	char buf[100];
	int nsfd=*(int *)arg;
	//while(1)
	//{
	recv(nsfd,buf,100,0);
	printf("msg rcvd is:%s\n",buf);
	gets(buf);
	send(nsfd,buf,100,0);
	//}
}


char buf1[100];
void *udp_service(void *arg)//thread for udp service
{       printf("thread\n");
	int udp=*(int *)arg;
	struct sockaddr_in client1;
	int length1;
	recvfrom(udp,buf1,100,0,(struct sockaddr*)&client1,&length1);
				printf("msg received from in udp is %s\n",buf1);
	gets(buf1);
	sendto(udp,buf1,100,0,(struct sockaddr*)&client1,sizeof(client1));
}





int main()
{
int i,j,tsfd[5],usfd[5];
struct sockaddr_in server_tcp,server_udp,client_tcp,client_udp;


for(i=0;i<5;i++)
{

tsfd[i]=socket(AF_INET,SOCK_STREAM,0);//creating 5 tcp socket
if(tsfd[i]==-1)
{

perror("tcp socket");exit(1);
}
server_tcp.sin_family=AF_INET;
server_tcp.sin_port=htons(1500+i);
server_tcp.sin_addr.s_addr=INADDR_ANY;
if(bind(tsfd[i],(struct sockaddr *)&server_tcp,sizeof(server_tcp))==-1)//binding tcp socket
{perror("tcp bind error");exit(1);}
listen(tsfd[i],5);
usfd[i]=socket(AF_INET,SOCK_DGRAM,0);//creating 5 udp socket
if(usfd[i]==-1)
{
perror("udp socket");exit(1);
}
server_udp.sin_family=AF_INET;
server_udp.sin_port=htons(2000+i);
server_udp.sin_addr.s_addr=INADDR_ANY;
if(bind(usfd[i],(struct sockaddr *)&server_udp,sizeof(server_udp))==-1)//binding udp socket
{perror("udp bind error");exit(1);}
}
struct timeval tv;
tv.tv_sec=10;
tv.tv_usec=0;
fd_set rd,wr,er;
FD_ZERO(&rd);
FD_ZERO(&wr);
FD_ZERO(&er);
while(1)
{

for(i=0;i<5;i++)
{
FD_SET(tsfd[i],&rd);
FD_SET(usfd[i],&rd);
}

int f=select(FD_SETSIZE,&rd,NULL,NULL,&tv);//select system call
for(i=0;i<5;i++)
{

int length;
if(FD_ISSET(tsfd[i],&rd))//checking which tcp  is active

{
length=sizeof(client_tcp);
int nsfd=accept(tsfd[i],(struct sockaddr *)&client_tcp,&length);
if(nsfd==-1)
{printf("accept error");exit(1);
}
pthread_t p;

			pthread_create(&p,NULL,&tcp_service,(void *)&nsfd);//creating tcp thread
			pthread_join(p,NULL);


			tv.tv_sec=10;
			tv.tv_usec=0;
			FD_CLR(tsfd[i],&rd);
}

if(FD_ISSET(usfd[i],&rd))//checking which udp is active
{
pthread_t p;
char buf[100];
pthread_create(&p,NULL,&udp_service,(void *)&usfd[i]);//creating udp thread
pthread_join(p,NULL);

tv.tv_sec=10;
tv.tv_usec=0;
FD_CLR(usfd[i],&rd);

}

}
}
return 0;
}
