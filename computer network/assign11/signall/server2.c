
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/un.h>
#include<errno.h>
#include<signal.h>
#define PATH "socket"
char buf2[100];
int x;
int passfd;
void handler()
{
	printf("handler\n");
	while(1)
	{
	if(read(passfd,buf2,10)<0)
	perror("read");
	printf("%s\n",buf2);
	kill(x,SIGUSR1);sleep(2);
}
	
}

int main()
{
	signal(SIGUSR1,handler);
	perror("signal");
	char path[100];
	char path2[100];
	int p=getpid();
	mkfifo("first",0666);
	int k=open("first",0666);
	char buf2[100];
	sprintf(buf2,"%d\n",p);
	write(k,buf2,sizeof(buf2));
	printf("process id is %s\n",buf2);

	int usfd,nsfd,size;
	char s='1';
	struct sockaddr_un ss,ss2;
	bzero(&ss,sizeof(ss));
	ss.sun_family=AF_UNIX;
	sprintf(path,".");
	sprintf(path2,"%s/%d",path,p);
	

	
	
	strcpy(ss.sun_path,path2);
	
	size=sizeof(struct sockaddr);
	usfd=socket(AF_UNIX,SOCK_STREAM,0);
	
	unlink(path2);
	if(bind(usfd,(struct sockaddr *)&ss,sizeof(ss))<0)
	
		perror("bind()");
	printf("bind path is %s\n",ss.sun_path);
	if(listen(usfd,20)<0)
		perror("bind");
	//printf("ddd%s\n",ss2.sun_path);
	if((nsfd=accept(usfd,(struct sockaddr *)&ss2,&size))==-1)
	{
		perror("accept\n");
		exit(1);
	}
	printf("accept path %s\n",ss2.sun_path);
	int i;
	char to[10];
	int j=0;
	for(i=2;i<6;i++)
	{
	to[j++]=ss2.sun_path[i];
	}
	to[j]='\0';
	printf("%s\n",to);
	x=atoi(to);
	printf("killing:%d\n",x);
	

	
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
	
	
	int x=recvmsg(nsfd,&msg,0);
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
	memcpy(&passfd,CMSG_DATA(cmsg),sizeof passfd);
	printf("%d\n",passfd);
	
	
	
	while(1);
	close(usfd);
	close(nsfd);
	
	return 0;
}
