#include<stdlib.h>
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<pthread.h>
#include<netinet/in.h>
#include<errno.h>
#include<string.h>
int main()
{
	int length,k;
	char buf[100];
	struct sockaddr_in client,server;
	int sfd=socket(AF_INET,SOCK_DGRAM,0);
	server.sin_family=AF_INET;
	printf("enter port no to be connected\n");
	scanf("%d\n",&k);
	server.sin_port=htons(k);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	length=sizeof(server);
	
	while(1)
	{
	gets(buf);
	printf("msg sent :%s\n",buf);
	if(sendto(sfd,buf,100,0,(struct sockaddr *)&server,(sizeof(server)))==-1)
		printf("error %s\n",strerror(errno));
	if(recvfrom(sfd,buf,100,0,(struct sockaddr *)&server,&length)==-1)
		printf("recv error\n");
	printf("msg receved is:%s\n",buf);
	}
	return 0;
}
	
