#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<time.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>

int main()
{
int sfd,nsfd,pid,length;
struct sockaddr_in my_addr,server_addr;
if((sfd=socket(AF_INET,SOCK_STREAM,0))<0)
{printf("Server: Socket Error:%d\n",errno);exit(0);}
bzero((char *)&my_addr,sizeof(my_addr));
my_addr.sin_family=AF_INET;
my_addr.sin_port=htons(5500);
my_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
connect(sfd,(struct sockaddr *)&my_addr,sizeof(my_addr));
printf("Enter File Name\n");
char  buf[256];
fgets(buf,256,stdin);

send(sfd,buf,256,0);
char msg[4096];
while(1)
{

recv(sfd,buf,4096,0);
printf("%s",buf);

memset(buf,0,4096);

}

}


