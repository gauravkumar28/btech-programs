#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netdb.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
char buf[100];
int c;
int sfd,nsfd;
socklen_t clientsize;

sfd=socket(AF_INET,SOCK_STREAM,0);
if(sfd==-1)
{
printf("socket error\n");exit(0);}


struct sockaddr_in server,client;
bzero((char*)&server,sizeof(server));
server.sin_family=AF_INET;
server.sin_addr.s_addr=htons(INADDR_ANY);
server.sin_port=htons(1500);
if(bind(sfd,(struct sockaddr *)&server,sizeof(server))<0)
{
printf("bind error");exit(0);}
printf("seela");

listen(sfd,10);
while(1)
{
clientsize=sizeof(client);
printf("seela");
nsfd=accept(sfd,(struct sockaddr *)&client,&clientsize);
if(nsfd<0)
{
printf("error");exit(1);
}
memset(buf,0,100);
recv(nsfd,buf,100,0);
printf("%s",buf);

int a=atoi(buf);

switch(a)
{
case 1:
{c=fork();
if(c==0)
{
close(sfd);
dup2(nsfd,1);
execv("./p1",NULL);

}

else if(c>0)
{
close(nsfd);

}

break;
}
case 2:
{
c=fork();
if(c==0)
{
close(sfd);
dup2(nsfd,1);
execv("./p2",NULL);
}

else if(c>0)
{printf("hi");
close(nsfd);

}
break;

}
case 3:
{c=fork();
if(c==0)
{
close(sfd);
dup2(nsfd,1);
execv("./p3",NULL);
}

else if(c>0)
{
close(nsfd);

}

break;
}
case 4:
{c=fork();

if(c==0)
{
close(sfd);
dup2(nsfd,1);
execv("./p4",NULL);
}

else if(c>0)
{
close(nsfd);

}

break;
}
}
}

return 0;
}
