#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
int main()
{
int sfd,j;
char buf[100];
struct sockaddr_in me,server;

server.sin_family=AF_INET;
server.sin_port=htons(3500);
inet_pton(AF_INET,"127.0.0.1",&server.sin_addr);
memset(&(server.sin_zero),'\0',8);

if((sfd=socket(AF_INET,SOCK_STREAM,0))==-1)
{
printf("\nsocket creation error");
exit(1);
}

if(connect(sfd,(struct sockaddr *)&server,sizeof(struct sockaddr))==-1)
{
perror("\nConnecting error");
exit(1);
}
while(1)
{
printf("enter msg\n");
gets(buf);
send(sfd,buf,100,0);
printf("Server->%s\n",buf);
recv(sfd,buf,100,0);
	printf("msg received is%s\n",buf);
}
close(sfd);
return 0;
}
