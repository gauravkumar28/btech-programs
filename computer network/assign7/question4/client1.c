#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>



int main(int argc,char* argv[])
{
int sfd,nsfd,size2;
char buf[100],sbuf[10];
struct sockaddr_in group1,g1g2,group2;
sfd=socket(AF_INET,SOCK_STREAM,0);
if(sfd==-1)
{printf("socket error\n");exit(1);}

bzero((char*)&group1,sizeof(group1));
group1.sin_family=AF_INET;
group1.sin_addr.s_addr=inet_addr("127.0.0.1");
group1.sin_port=htons(2500);

if(connect(sfd,(struct sockaddr *)&group1,sizeof(group1))==-1)
{perror("hehe");exit(1);}

memset(buf,0,100);memset(sbuf,0,10);
strcpy(buf,argv[1]);
printf("enter group two port no\n");
gets(sbuf);
strcat(buf," ");
strcat(buf,sbuf);
if(send(sfd,buf,100,0)==-1)
{printf("send error\n");exit(1);}
int newsfd=socket(AF_INET,SOCK_STREAM,0);
if(newsfd==-1)
{printf("sock error\n");exit(1);}

bzero(&g1g2,sizeof(g1g2));
g1g2.sin_family=AF_INET;
g1g2.sin_addr.s_addr=htonl(INADDR_ANY);

g1g2.sin_port=htons(atoi(argv[1]));

//printf("ram\n");

if((bind(newsfd,(struct sockaddr *)&g1g2,sizeof(g1g2)))==-1)
{perror("+++");exit(1);}
listen(newsfd,5);
size2=sizeof(group2);
nsfd=accept(newsfd,(struct sockaddr *)&group2,&size2);
//printf("shyam\n");
if(nsfd==-1)
{perror("error");exit(1);}
while(1)
{memset(buf,0,100);
recv(nsfd,buf,100,0);
printf("%s\n",buf);
memset(buf,0,100);
gets(buf);
send(nsfd,buf,100,0);

}


return 0;
}
