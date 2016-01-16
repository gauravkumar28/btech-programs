#include<stdio.h>
#include<unistd.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<poll.h>


int main()
{
struct pollfd p[2];

int tsfd,usfd,nsfd,tcpsize,udpsize;
int pstatus;
struct sockaddr_in tcpserver,udpserver,tcpclient,udpclient;
tsfd=socket(AF_INET,SOCK_STREAM,0);//tcp socket
if(tsfd==-1)
{printf("socket error");exit(1);}
usfd=socket(AF_INET,SOCK_DGRAM,0);//udp socket
if(usfd==-1)
{printf("socket error");exit(1);}
bzero(&tcpserver,sizeof(tcpserver));
tcpserver.sin_family=AF_INET;
tcpserver.sin_addr.s_addr=INADDR_ANY;
tcpserver.sin_port=htons(1500);
if(bind(tsfd,(struct sockaddr *)&tcpserver,sizeof(tcpserver))==-1)//tcp bind
{printf("bind error\n");exit(1);}
udpserver.sin_family=AF_INET;
udpserver.sin_addr.s_addr=INADDR_ANY;
udpserver.sin_port=htons(2000);
if(bind(usfd,(struct sockaddr *)&udpserver,sizeof(udpserver))==-1)//udp bind
{printf("bind error\n");exit(1);}
listen(tsfd,5);
p[0].events=POLLIN;
p[1].events=POLLIN;
p[0].fd=tsfd;
p[1].fd=usfd;
while(1)
{

pstatus=poll(p,2,2000);//polling tcp and udp  connection

if(pstatus>0)
{
if(p[0].revents&POLLIN)//tcp request
{

tcpsize=sizeof(tcpclient);
nsfd=accept(tsfd,(struct sockaddr*)&tcpclient,&tcpsize);//accepting tcp connection
int c=fork();//creating chield for each tcp client
if(c==0)
{
close(tsfd);
char tcpbuf[100];
while(1)
{

recv(nsfd,tcpbuf,100,0);
printf("tcp client says\t%s\n",tcpbuf);
printf("message\n");
memset(tcpbuf,0,100);
gets(tcpbuf);
send(nsfd,tcpbuf,100,0);
memset(tcpbuf,0,100);
}
}
else if(c>0)
close(nsfd);
}
if(p[1].revents&POLLIN)//udp request

{
udpsize=sizeof(udpclient);
char udpbuf[100];
memset(udpbuf,0,100);

recvfrom(usfd,udpbuf,100,0,(struct sockaddr*)&udpclient,&udpsize);
printf("message from %s with port no %d is %s\n",inet_ntoa(udpclient.sin_addr),ntohs(udpclient.sin_port),udpbuf);
memset(udpbuf,0,100);
printf("messge is\n");
gets(udpbuf);
sendto(usfd,udpbuf,100,0,(struct sockaddr *)&udpclient,udpsize);
}


}

}
return 0;
}
