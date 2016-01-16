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
fd_set rd,wr,er;//set fd  for read write and error
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

int f=select(FD_SETSIZE,&rd,NULL,NULL,&tv);//selecting tcp  or udp request  based on parameters
for(i=0;i<5;i++)
{

int length;
if(FD_ISSET(tsfd[i],&rd))//checking which tcp request is active

{
length=sizeof(client_tcp);
int nsfd=accept(tsfd[i],(struct sockaddr *)&client_tcp,&length);//accepting tcp request
if(nsfd==-1)
{printf("accept error");exit(1);
}
int k=fork();
if(k==0)
{
for(j=0;j<5;j++)
					close(tsfd[j]);

				dup2(nsfd,0);//duplicating file discriptor to read
				dup2(nsfd,1);//duplicating file discriptor to write
				execl("./s1",NULL,NULL);//calling another application  ./s1 is not added here u can add any executable program here


}
else
close(nsfd);
tv.tv_sec=10;
tv.tv_usec=0;
FD_CLR(tsfd[i],&rd);

}

if(FD_ISSET(usfd[i],&rd))//checking which udp request came
{length=sizeof(client_udp);
int k=fork();
			if(k==0)
			{
				char buf[100];
				recvfrom(usfd[i],buf,100,0,(struct sockaddr*)&client_udp,&length);
				printf("msg received from %d in udp is %s\n",i,buf);
gets(buf);
sendto(usfd[i],buf,100,0,(struct sockaddr*)&client_udp,length);

			}
			tv.tv_sec=10;
			tv.tv_usec=0;
			FD_CLR(usfd[i],&rd);

}

else
{
printf("NO DATA AVAILABLE in recent 10 seconds\n");
                  	tv.tv_sec = 10;
                  	tv.tv_usec = 0;

}
}
}
return 0;
}
