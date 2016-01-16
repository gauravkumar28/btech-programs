#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>

int main(int argc,char* argv[])
{
char buf[100];
int sfd;
struct sockaddr_in client;



sfd=socket(AF_INET,SOCK_STREAM,0);
if(sfd==-1)
{printf("socket error\n");exit(1);}

if(argc<3)
{printf("argument error\n");exit(1);}

client.sin_family=AF_INET;
client.sin_addr.s_addr=inet_addr(argv[1]);
client.sin_port=htons(atoi(argv[2]));
if(connect(sfd,(struct sockaddr *)&client,sizeof(client))<0)
{printf("coonet error");exit(0);}
while(1)
{

printf("type service u want");
memset(buf,0,100);
gets(buf);
send(sfd,buf,100,0);
memset(buf,0,100);
read(sfd,buf,100);
printf("%s",buf);
}
return 0;
}
