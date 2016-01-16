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
void* service(void* x)
{
int p=*((int*)x);

	while(1)
	{
	char buf[100];
	printf("aa\n");
	recv(p,buf,100,0);
	printf("pp\n");
	printf("msg rcvd is %s\n",buf);
	printf("enter msg\n");
	gets(buf);
	send(p,buf,100,0);
	}
}


int main()
{	pthread_t t[1000];
	int iter=0;
	int unfd=socket(AF_LOCAL,SOCK_STREAM,0);
	struct sockaddr_un addr;
	addr.sun_family=AF_LOCAL;
	strncpy(my.sun_path,"/temp/unix.str",sizeof(my.sun_path)-1);
	unlink("/tmp/unix.str");
	if(bind(unfd,(struct sockaddr*)&addr,sizeof addr)<0)
		{
			printf("Bind error.\n");
			exit(0);
		}
		struct sockaddr_un addr2;
		socklen_t len;
		listen(unfd,10);
		int cfd=accept(unfd,(struct sockaddr*)&addr2,&len);
		int cfd2=0;
		while(cfd2!=-1)
		{
			struct msghdr msg={0};
			char buf[CMSG_SPACE(sizeof(int))];
			msg.msg_control=buf;
			msg.msg_controllen=sizeof buf;
		
			char p1[1]={'a'};
			struct iovec base;
			base.iov_base=p1;
			base.iov_len=1;
		
			msg.msg_iov=&base;
			msg.msg_iovlen=1;
		
	
			int x=recvmsg(cfd,&msg,0);
			if(x<0)
			{
				printf("recvmsg error\n");
			}
			struct cmsghdr* cmsg=CMSG_FIRSTHDR(&msg);
			if(cmsg==NULL||cmsg->cmsg_type!=SCM_RIGHTS)
			{
				//printf("Didnt recieve fd\n");
			}
			else
			{
			int passfd;
			
			
			if(memcpy(&passfd,CMSG_DATA(cmsg),sizeof passfd)>0)
				pthread_create(&t[iter++],NULL,service,(void*)&passfd);
			}
			
		}
			pthread_join(t[0],NULL);
	return 0;

}
