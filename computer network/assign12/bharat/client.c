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
int main()
{
	char buf[100];
	int sfd=socket(AF_INET,SOCK_RAW,0);
	recv(sfd,buf,100,0);
	printf("msg recvd is%s",buf);
	printf("enter msg to send\n");
	gets(buf);
	send(sfd,buf,100,0);
	
	return 0;
}
