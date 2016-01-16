#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/select.h>
#include<sys/un.h>
#include<netinet/ip.h>
#include<netinet/udp.h>

int main()
{
int usfd=socket(AF_INET,SOCK_DGRAM,0);
if(usfd==-1)
perror("sock error\n");
struct sockaddr_in servaddr,clientaddr;
socklen_t length=sizeof(struct sockaddr_in);
servaddr.sin_family=AF_INET;
servaddr.sin_port=htons(2300);
servaddr.sin_addr.s_addr=INADDR_ANY;
int b=bind(usfd,(struct sockaddr*)&servaddr,sizeof(struct sockaddr_in));
if(b<0)
perror("Bind error\n");

while(1)
{
char msg[512]={0};	
recvfrom(usfd,msg,512,0,(struct sockaddr*)&clientaddr,&length);
printf(" msg received from client of port id %d\n",htons(clientaddr.sin_port));
printf("msg received is:%s",msg);
printf("enter msg to send \n");
gets(msg);
sendto(usfd,msg,512,0,(struct sockaddr*)&clientaddr,length);
	
}
return 0;
}
