#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/in.h>
int main()
{
char buf[100];
int sfd;
sfd=socket(AF_INET,SOCK_STREAM,0);//tcp socket
struct sockaddr_in client;
bzero(&client,sizeof(client));
client.sin_family=AF_INET;
client.sin_addr.s_addr=inet_addr("127.0.0.1");
client.sin_port=htons(1500);

connect(sfd,(struct sockaddr*)&client,sizeof(client));//connecting to server
while(1)
{
memset(buf,0,100);
printf("message\n");
gets(buf);
send(sfd,buf,100,0);
memset(buf,0,100);
recv(sfd,buf,100,0);
printf("server said\t%s\n",buf);
}


return 0;
}


