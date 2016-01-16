#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<stdio.h>
#define NAME "socket"
int main()
{
	struct sockaddr_un server;
	int sfd=socket(AF_UNIX,SOCK_STREAM,0);
	memset(&server,0,sizeof(struct sockaddr_un));
	server.sun_family=AF_UNIX;
	strcpy(server.sun_path,NAME);
	if(connect(sfd,(struct sockaddr*)&server,sizeof(struct sockaddr_un)))
		perror("connect error\n");
	struct msghdr msg={0};
	char buf[CMSG_SPACE(sizeof(int))];
	msg.msg_control=buf;
	msg.msg_controllen=sizeof buf;
	
	char p[1]={'a'};
	struct iovec base;
	base.iov_base=p;
	base.iov_len=1;
	
	msg.msg_iov=&base;
	msg.msg_iovlen=1;
	
	
	int x=recvmsg(sfd,&msg,0);
	if(x<0)
	{
	printf("recvmsg error\n");
	return -1;
	}
	struct cmsghdr* cmsg=CMSG_FIRSTHDR(&msg);
	if(cmsg==NULL||cmsg->cmsg_type!=SCM_RIGHTS)
	{
	printf("Didnt recieve fd\n");
	return -1;
	}
	int passfd;
	memcpy(&passfd,CMSG_DATA(cmsg),sizeof passfd);
	printf("%d\n",passfd);
	printf("enter msg\n");
	char buf2[]="haiii";;
	//gets(buf2);
	/*write(passfd,buf2,100);
	read(passfd,buf2,100);*/
	send(passfd,buf2,strlen(buf2),0);
	printf("msg from server %s\n",buf);
	close(sfd);
	return 0;
}
	
