#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<netdb.h>
struct detail
{
int port;
char ip[30];
}d[10];
int count=0;

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

int i;
for(i=0;i<count;i++)
{
if(d[i].port==ntohs(client.sin_port)&&!strcmp(d[i].ip,inet_ntoa(client.sin_addr)))
break;
//printf("ram\n");
}

 if(i==count)
{

d[count].port=ntohs(client.sin_port);
memset(d[i].ip,0,30);
strcpy(d[count].ip,inet_ntoa(client.sin_addr));
printf("%s\n",d[i].ip);
count++;
if(count==1)
{

printf("no other client available\n");
}
else
{
printf("enter your message\n");
memset(buf,0,100);
gets(buf);
int j;
for(j=0;j<count-1;j++)
{
printf("nitish\n");
client.sin_addr.s_addr=inet_addr(d[j].ip);
client.sin_port=htons(d[j].port);
client.sin_family=AF_INET;
sendto(sfd,buf,100,0,(struct sockaddr *)&client,sizeof(client));
}
}
}
else if(i<count)
{

printf("enter your message\n");
memset(buf,0,100);
gets(buf);
int j;
for(j=0;j<count;j++)
{
if(j!=i)
{
client.sin_addr.s_addr=inet_addr(d[j].ip);
client.sin_port=htons(d[j].port);
client.sin_family=AF_INET;
sendto(sfd,buf,100,0,(struct sockaddr *)&client,sizeof(client));
}}
}
}
return 0;
}
