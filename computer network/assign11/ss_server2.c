
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/un.h>
#include<errno.h>
#define PATH "socket"
int recvfd(int nsfd)
{
char s='1';
struct msghdr m;
struct iovec io;
io.iov_base=&s;
io.iov_len=sizeof(s);

memset(&m,0,sizeof(m));
m.msg_name=NULL;
m.msg_namelen=0;
m.msg_iov=&io;
m.msg_iovlen=1;
m.msg_flags=0;
char buf[CMSG_SPACE(sizeof(int))];
m.msg_control=buf;
m.msg_controllen=sizeof(buf);

recvmsg(nsfd,&m,0);

struct cmsghdr *cm;
cm=CMSG_FIRSTHDR(&m);
return *((int *)CMSG_DATA(cm));
}
int main()
{
int usfd,nsfd,rsfd,size;
char s='1';
struct sockaddr_un ss,ss2;
bzero(&ss,sizeof(ss));
ss.sun_family=AF_UNIX;
unlink(PATH);
strncpy(ss.sun_path,PATH,sizeof(ss.sun_path)-1);

size=sizeof(struct sockaddr);
usfd=socket(AF_UNIX,SOCK_STREAM,0);
int b1=bind(usfd,(struct sockaddr *)&ss,sizeof(ss));
if(b1<0)
perror("bind()");
listen(usfd,SOMAXCONN);
if((nsfd=accept(usfd,(struct sockaddr *)&ss2,&size))==-1)
{
perror("accept\n");
exit(1);
}
/*	
struct msghdr m;
struct iovec io;
io.iov_base=&s;
io.iov_len=sizeof(s);

memset(&m,0,sizeof(m));
m.msg_name=NULL;
m.msg_namelen=0;
m.msg_iov=&io;
m.msg_iovlen=1;
m.msg_flags=0;
char buf[CMSG_SPACE(sizeof(int))];
m.msg_control=buf;
m.msg_controllen=sizeof(buf);

recvmsg(nsfd,&m,0);

struct cmsghdr *cm;
cm=CMSG_FIRSTHDR(&m);
recvsfd=*((int *)CMSG_DATA(cm));*/
rsfd=recvfd(nsfd);
	printf("%d\n",rsfd);
char buf2[]="The Requested Service is serving you";
send(rsfd,buf2,100,0);

close(usfd);
close(nsfd);
close(rsfd);
return 0;
}
