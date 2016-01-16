#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/un.h>
#include<errno.h>
#include<fcntl.h>
#include<sys/stat.h>
#define path "socket"
int sfd,nsfd,usfd,size;
struct sockaddr_un his,my;
struct sockaddr_in server,client;
struct msghdr msg;
struct iovec io;
char s='1';

void sendfd(int unfd,int fds)
{

struct msghdr msg={0};//clear the msghdr

		char buf[CMSG_SPACE(sizeof(int))];//allocate needed space
		msg.msg_control=buf;//allocate buffer to msghdr
		msg.msg_controllen=sizeof buf;//length of buffer
		char p[1]={'a'};
		
		struct iovec base;
		base.iov_base=p;
		base.iov_len=1;
		
		msg.msg_iov=&base;
		msg.msg_iovlen=1;
		
		struct cmsghdr* cmsg=CMSG_FIRSTHDR(&msg);//get first CMSG_HDR
		cmsg->cmsg_level=SOL_SOCKET;
		cmsg->cmsg_type=SCM_RIGHTS;//passing fd
		cmsg->cmsg_len=CMSG_LEN(sizeof(int));//size of one fd
		memcpy(CMSG_DATA(cmsg),&fds,sizeof fds);//copy argument fd into cmsg data
		msg.msg_controllen=cmsg->cmsg_len;//length reset for sending
		int x=sendmsg(unfd,&msg,0);
		//sendmsg returning 0...thus msg not being sent
		if(x<0)
		{
			printf("send error.\n");
			exit(0);
		}
}
int main()
{

server.sin_family=AF_INET;
server.sin_port=1240;
server.sin_addr.s_addr=htonl(INADDR_ANY);
memset(&(server.sin_zero),'\0',8);

size=sizeof(struct sockaddr_in);

bzero(&client,sizeof(client));

sfd=socket(AF_INET,SOCK_STREAM,0);
setsockopt(sfd,SOL_SOCKET,SO_REUSEADDR,&s,sizeof(int));
int b1=bind(sfd,(struct sockaddr *)&server,sizeof(server));
if(b1<0)
perror("bind()");
listen(sfd,5);
nsfd=accept(sfd,(struct sockaddr *)&client,&size);
printf("%d\n",nsfd);

bzero(&my,sizeof(my));
my.sun_family=AF_UNIX;
strncpy(my.sun_path,path,sizeof(my.sun_path)-1);
usfd=socket(AF_UNIX,SOCK_STREAM,0);
int con=connect(usfd,(struct sockaddr *)&my,sizeof(my));
if(con==-1)
perror("connect");
sendfd(usfd,nsfd);
/*printf("before sendin2\n");
io.iov_base=&s;
io.iov_len=sizeof(s);
memset(&msg,0,sizeof(msg));
msg.msg_name=NULL;
msg.msg_namelen=0;
msg.msg_iov=&io;
msg.msg_iovlen=1;
msg.msg_flags=0;
char buf[CMSG_SPACE(sizeof(int))];
msg.msg_control=buf;
msg.msg_controllen=sizeof(buf);
struct cmsghdr *cm;
cm=CMSG_FIRSTHDR(&msg);

cm->cmsg_len=CMSG_LEN(sizeof(int));
printf("before sendin1\n");
cm->cmsg_level=SOL_SOCKET;
cm->cmsg_type=SCM_RIGHTS;

*((int*)CMSG_DATA(cm))=nsfd;
printf("before sendin\n");*/
sendmsg(usfd,&msg,0);
close(nsfd);
close(sfd);
return 0;
}
