#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/unistd.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<string.h>
#include<pthread.h>
#define ip "127.0.0.1"
#define port 2351

int createsocket()
{
	struct sockaddr_in claddr;
	int tmpsfd;
	tmpsfd=socket(AF_INET,SOCK_STREAM,0);
		perror("socket status : ");

    memset(&claddr,0,sizeof(claddr));

	claddr.sin_family=AF_INET;	
	claddr.sin_port=htons(port);
	inet_pton(AF_INET,ip,&claddr.sin_addr);
		  perror("ip status :");

    connect(tmpsfd,(struct sockaddr *)&claddr,sizeof(claddr));
    return tmpsfd;
}

main()
{
	int sfd = createsocket();
	int n,prs;
	char buf[50];
if(fork()>0)
{
    while(1)
    {
		printf("group : \n");
		scanf("%d",&n);	
		sprintf(buf,"%d",n);
		send(sfd,buf,sizeof(buf),0);
		memset(buf,0,sizeof(buf));	

		printf("enter process \n");
		scanf("%d",&prs);
		sprintf(buf,"%d",prs);	
		send(sfd,buf,sizeof(buf),0);
		memset(buf,0,sizeof(buf));	

		gets(buf);
		memset(buf,0,sizeof(buf));
		gets(buf);
		send(sfd,buf,sizeof(buf),0);
		memset(buf,0,sizeof(buf));	
	}
}
else
{
    	recv(sfd,buf,sizeof(buf),0);
	    printf("%s\n",buf);
		memset(buf,0,sizeof(buf));
}	

}

