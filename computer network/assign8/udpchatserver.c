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
server.sin_addr.s_addr=htonl(INADDR_ANY);
server.sin_port=htons(1500);
bind(sfd,(struct sockaddr *)&server,sizeof(server));
size=sizeof(client);
while(1)
{
memset(buf,0,100);
if((recvfrom(sfd,buf,100,0,(struct sockaddr *)&client,&size))==-1)
exit(1);
printf("recieved from %s with port no %d  messaage  \t%s\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port),buf);
printf("enter your message\n");
memset(buf,0,100);
gets(buf);
sendto(sfd,buf,100,0,(struct sockaddr *)&client,sizeof(client));
}
return 0;
}
