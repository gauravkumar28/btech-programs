#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>

int main()
{
char buf[100];
int sfd,size;
sfd=socket(AF_INET,SOCK_DGRAM,0);
if(sfd==-1)
{
printf("error in socket");exit(1);}

struct sockaddr_in server,client;
server.sin_family=AF_INET;
server.sin_addr.s_addr=inet_addr("127.0.0.1");
server.sin_port=htons(2000);
size=sizeof(client);
while(1)
{memset(buf,0,100);
printf("your message \n");
gets(buf);

sendto(sfd,buf,100,0,(struct sockaddr *)&server,sizeof(server));

memset(buf,0,100);

recvfrom(sfd,buf,100,0,(struct sockaddr *)&client,&size);
printf("%s\n",buf);
}
return 0;
}
