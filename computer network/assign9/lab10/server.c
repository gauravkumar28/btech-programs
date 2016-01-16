#include<stdio.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/types.h>
#include<sys/select.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<fcntl.h>
#include<stdlib.h>


int main()
{
	struct sockaddr_in server,client;
	int sfd=socket(AF_INET,SOCKSTREAM,0);
	server.sin_family=AF_INET;
	server.sin_port=htons(3500);
	server.sin_addr.s_addr=INADDR_ANY;
	bind(sfd,(struct sockaddr *)&server,(sizeof(server)));
	listen(sfd,20);

	int maxfd,maxi=-1,clt[FD_SETSIZE],i,sockfd;
	for(i=0;i<FD_SETSIZE;i++)
		clt[i]=-1;
	maxfd=sfd;
	fd_set rset,allset;
	FD_ZERO(&allset);
	FD_SET(sfd,&allset);
	for(;;)
	{
		rset=allset;
		int nready=select(maxfd+1,&rset,NULL,NULL,NULL);
		if(FD_ISSET(sfd,&rset))
		{
			int length=sizeof(client);
			int nsfd=accept(sfd,(struct sockaddr*)&client,&length);
			FD_SET(nsfd,&allset);
			for(i=0;i<FD_SETSIZE;i++)
			{
				if(clt[i]<0)
				{
					clt[i]=sfd;
					break;
				}
			}
			if(i==FD_SETSIZE)
				printf("ERROR:Too many clients\n");
			FD_SET(sfd,&allset);
			if(nsfd>maxfd)
				maxfd=nsfd;
			if(i>maxi)
				maxi=i;
			if(--nsfd<=0)
				continue;
		}
		for(i=0;i<=maxi;i++)
		{
			if((sockfd=clt[i])<0)
			{
				continue;
			if(FD_ISSET(sockfd,&rset))
			{
				if((	<0))
				{
				
					FD_CLR(sockfd,&allset);
					client[i]=-1;
				}
				else
				{
		

				}
		
				if(--nready<=0)
					break;
			}
		}
	}
	return 0;
}
		
			

