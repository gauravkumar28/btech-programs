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
#include<signal.h>
#define NAME "socket"
#define NAME2 "socket1"
int fd,k,w;
char buf2[100];
void handler()
{
	printf("handler\n");
	while(1){
		
read(w,buf2,10);
printf("%s\n",buf2);
kill(k,SIGUSR1);sleep(2);
}
}
int main()
{
	signal(SIGUSR1,handler);
	char path[100];
	char path2[100];
	char buf1[5];
	int fd1=open("first",0666);
	read(fd1,buf1,5);

	int fd=open("./p1.txt",O_RDWR);
	w=fd;
	perror("fd error");
	printf("%d\n",fd);
	k=atoi(buf1);
	//printf("%d\n",k);

	
	
	int nunfd,length;
	struct sockaddr_un server,client;
	int unfd=socket(AF_UNIX,SOCK_STREAM,0);
	
	
	server.sun_family=AF_UNIX;
	
	sprintf(path,".");
	sprintf(path,"%s/%d",path,k);
	sprintf(path2,".");
	sprintf(path2,"%s/%d",path2,getpid());
	
	strcpy(server.sun_path,path2);
	unlink(path2);
	if(bind(unfd,(struct sockaddr*)&server,sizeof(struct sockaddr_un))<0)
		perror("bind error");
	printf("Socket has name %s\n", server.sun_path);
	client.sun_family=AF_UNIX;
	strcpy(client.sun_path,path);	
	if(connect(unfd,(struct sockaddr*)&client,(sizeof(struct sockaddr_un)))<0)
		perror("connect error");
	printf("connect socket has name %s\n",client.sun_path);
	

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
	memcpy(CMSG_DATA(cmsg),&fd,sizeof fd);//copy argument fd into cmsg data
	msg.msg_controllen=cmsg->cmsg_len;
	int x=sendmsg(unfd,&msg,0);
	
	if(x<0)
	{
		printf("send error.\n");
		exit(0);
	}
	printf("killing %d\n",k);
	kill(k,SIGUSR1);
	while(1);
	close(fd);
	return 0;
}
