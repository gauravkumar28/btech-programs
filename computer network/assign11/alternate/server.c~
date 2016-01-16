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

int fds[1000]={0};
int iter=0;
int unfd,sfd;
void* service(void* x)
{
int p=*((int*)x);

	while(1)
	{
	char buf[100];
	if(recv(p,buf,100,0)<0)
	return;
	printf("msg rcvd is %s\n",buf);
	printf("enter msg\n");
	gets(buf);
	send(p,buf,100,0);
	}
}


int main()
{
	pthread_t t[1000];
	sfd=socket(AF_INET,SOCK_STREAM,0);
	unfd=socket(AF_LOCAL,SOCK_STREAM,0);
	struct sockaddr_in saddr;
	struct sockaddr_un uaddr;
	saddr.sin_family=AF_INET;
	saddr.sin_addr.s_addr=INADDR_ANY;
	saddr.sin_port=htons(3500);
	if(bind(sfd,(struct sockaddr*) &saddr,sizeof saddr)<0)
	{
		printf("Bind error\n");
		exit(0);
	}
	listen(sfd,10);
	uaddr.sun_family=AF_LOCAL;
	strcpy(uaddr.sun_path,"/tmp/unix.str");
	if(connect(unfd,(struct sockaddr*) &uaddr,sizeof uaddr)<0)
	{
		printf("connect error\n");
		exit(0);
	}
	while(iter<3)
	{
		struct sockaddr_in addr;
		socklen_t len=16;
		fds[iter]=accept(sfd,(struct sockaddr*)&addr,&len);
		pthread_create(&t[iter],NULL,service,(void*)&fds[iter]);
		iter++;
	}
	printf("server is down send to other server\n");
	int i=0;
	for(i=0;i<iter;i++)
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
		memcpy(CMSG_DATA(cmsg),&fds[i],sizeof fds[i]);//copy argument fd into cmsg data
		msg.msg_controllen=cmsg->cmsg_len;//length reset for sending
		int x=sendmsg(unfd,&msg,0);
		//sendmsg returning 0...thus msg not being sent
		if(x<0)
		{
			printf("send error.\n");
			exit(0);
		}
	}
	exit(0);
}
