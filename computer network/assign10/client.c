#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>
#include<netinet/in.h>
#include<errno.h>


int main(int argc,char* argv[])
{

char buf[100];
int sfd;

struct sockaddr_in client;
sfd=socket(AF_INET,SOCK_STREAM,0);
if(sfd==-1)
{printf("error in socket\n");exit(1);}
bzero((char*)&client,sizeof(client));
client.sin_family=AF_INET;
client.sin_addr.s_addr=inet_addr("127.0.0.1");
client.sin_port=htons(2500);
if((connect(sfd,(struct sockaddr *)&client,sizeof(client))==-1))
{perror("connection");exit(1);}
printf("ram\n");
while(1)
{
memset(buf,0,100);
printf("msg to server\n");
gets(buf);
send(sfd,buf,100,0);
memset(buf,0,100);
recv(sfd,buf,100,0);
printf("server said\t %s\n",buf);}
return 0;
}
