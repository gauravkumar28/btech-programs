#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<stdio.h>
#include<string.h>
#include<pthread.h>
#define NAME "socket"
int k=1;
int nsfd1[5],sfd1,length;

int main()
{
	pthread_t t;
	char buf[100];
 	struct sockaddr_un server;
	sfd1=socket(AF_UNIX,SOCK_STREAM,0);
	if(sfd1<0)
		perror("socket error");
	memset(&server,0,sizeof(struct sockaddr_un));
	
	server.sun_family=AF_UNIX;
	
	strcpy(server.sun_path,NAME);
	//snprintf(sadd.sun_path, UNIX_PATH_MAX, "./server.c");
	//if((strncpy(server.sun_path,"./temp",sizeof(server.sun_path)-1))>1)
		
	unlink(NAME);
	if(bind(sfd1,(struct sockaddr*)&server,sizeof(struct sockaddr_un)))
	{
		perror("bind error");
	}
	printf("Socket has name %s\n", server.sun_path);	
	if(listen(sfd1,20)!=0)
	{
		perror("listen error");
	}
	
	//pthread_create(&t,NULL,(void *)&service,NULL);
	while(1)
	{
		struct sockaddr_un client;

	nsfd1[k++]=accept(sfd1,(struct sockaddr*)&client,&length);
	/*if(k==2)
	{
		printf("k is %d\n",k);
		printf("ppp\n");
			read(nsfd1[1],buf,100);
			perror("read");
			printf("msg from clt %s\n",buf);
			gets(buf);
			write(nsfd1[1],buf,100);
			
	}*/

		
		if(k!=2)
		{
		printf("elsee\n");
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
		memcpy(CMSG_DATA(cmsg),&nsfd1[1],sizeof nsfd1[1]);//copy argument fd into cmsg data
		msg.msg_controllen=cmsg->cmsg_len;//length reset for sending
		int x=sendmsg(nsfd1[2],&msg,0);
		//sendmsg returning 0...thus msg not being sent
		if(x<0)
		{
			printf("send error.\n");
		}
	}
	}	//close(nsfd1);

		//close(nsfd1);
	close(sfd1);
	return 0;
}
