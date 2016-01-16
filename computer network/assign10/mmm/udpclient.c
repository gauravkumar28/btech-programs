#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	int sfd,n;
	char ch;
	char msg[40];
	struct sockaddr_in ser;
	sfd=socket(AF_INET,SOCK_DGRAM,0);
	bzero(&ser,sizeof(ser));
	ser.sin_family=AF_INET;
	int port;
	printf("enter the process\n");
	scanf("%d",&port);
	ser.sin_port=htons(port);
	ser.sin_addr.s_addr=htonl(INADDR_ANY);
	int s=sizeof(ser);
   // while(1)
    {  
    printf("enter the number\n");
    scanf("%s",msg);
	sendto(sfd,msg,40,0,(struct sockaddr *)&ser,sizeof(ser));
    
	recvfrom(sfd,msg,40,0,(struct sockaddr *)&ser,&s);
	//n=read(100,msg,20);
	//msg[n]=0;
	printf("%s\n",msg);
	}	
	return 0;
}
