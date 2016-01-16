#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
#include<stdio.h>
#include<pthread.h>
#define NAME "socket"
int sfd;
void *service(void *x)
{
	while(1)
	{
	printf("thread\n");
	char buf[100];
	//printf("enter msg\n");
	//gets(buf);
	//write(sfd,buf,100);
	recv(sfd,buf,sizeof(buf) ,0);
	int k=strcmp(buf,"haiii");
	if(k==0)
	{
	printf(" permission\n");
	exit(1);}
	}
}

int main()
{
	pthread_t t;
	struct sockaddr_un server;
	sfd=socket(AF_UNIX,SOCK_STREAM,0);
	memset(&server,0,sizeof(struct sockaddr_un));
	server.sun_family=AF_UNIX;
	strcpy(server.sun_path,NAME);
	if(connect(sfd,(struct sockaddr*)&server,sizeof(struct sockaddr_un)))
		perror("connect error\n");
	printf("ppp\n");
	pthread_create(&t,NULL,(void *)&service,NULL);
	while(1);
	return 0;
}
	
