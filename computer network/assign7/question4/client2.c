#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>


int main(int argc,char* argv[])
{
char buf[100];
int sfd,nsfd,asfd,bypasssize;
struct sockaddr_in group2,bypass,g2g1;


sfd=socket(AF_INET,SOCK_STREAM,0);
if(sfd==-1)
{printf("sock error\n");exit(1);}

group2.sin_family=AF_INET;
group2.sin_addr.s_addr=htonl(INADDR_ANY);
group2.sin_port=htons(atoi(argv[1]));

bind(sfd,(struct sockaddr *)&group2,sizeof(group2));

listen(sfd,5);
bypasssize=sizeof(bypass);

memset(buf,0,100);
nsfd=accept(sfd,(struct sockaddr *)&bypass,&bypasssize);
recv(nsfd,buf,100,0);

printf("%s",buf);
asfd=socket(AF_INET,SOCK_STREAM,0);
if(asfd==-1)
{printf("socket error");exit(1);}
bzero(&g2g1,sizeof(g2g1));

g2g1.sin_family=AF_INET;
g2g1.sin_addr.s_addr=inet_addr("127.0.0.1");
g2g1.sin_port=htons(atoi(buf));
if(connect(asfd,(struct sockaddr *)&g2g1,sizeof(g2g1))==-1)
{perror("error  ");exit(1);}
while(1)
{
memset(buf,0,100);
printf("msg to group1\n");
gets(buf);
send(asfd,buf,100,0);

memset(buf,0,100);
recv(asfd,buf,100,0);
printf("group 1 said%s\n",buf);}
return 0;
}
