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
	int i,j,sfd[5],usfd[5];
	struct sockaddr_in server,client,server1,client1;
	int big=-1,big1=-1;
	for(i=0;i<5;i++)
	{
		 sfd[i]=socket(AF_INET,SOCK_STREAM,0);
		usfd[i]=socket(AF_INET,SOCK_DGRAM,0);
		server.sin_family=AF_INET;
		server.sin_port=htons(3500+i+10);
		server.sin_addr.s_addr=INADDR_ANY;
		if(bind(sfd[i],(struct sockaddr*)&server,sizeof(server))<0)
			perror("error\n");
		listen(sfd[i],20);


		server1.sin_family=AF_INET;
		server1.sin_port=htons(3600+i);
		server1.sin_addr.s_addr=INADDR_ANY;
		if(bind(usfd[i],(struct sockaddr*)&server1,sizeof(server1))<0)
			perror("error:\n");
		
		
	}
	
	struct timeval tv;
	tv.tv_sec=10;
	tv.tv_usec=0;
	fd_set rd,wr,er;	
	FD_ZERO(&rd);
	FD_ZERO(&wr);
	FD_ZERO(&er);
	
	
	while(1)
	{
		for(i=0;i<5;i++)
		{
			FD_SET(sfd[i],&rd);
			
			FD_SET(usfd[i],&rd);
		}
		int f=select(FD_SETSIZE,&rd,NULL,NULL,&tv);
		//printf("%d\n",f);
	for(i=0;i<5;i++)
	{
		
		
		
		int length;
		if(FD_ISSET(sfd[i],&rd))	
		{			
			printf("msg received from %d in tcp \n",i);
			int nsfd=accept(sfd[i],(struct sockaddr*)&client,&length);
			if(nsfd<0)
                        perror("accept error\n");
			int k=fork();
			if(k==0)
			{
				for(j=0;j<5;j++)
					close(sfd[j]);
				
				dup2(nsfd,0);
				dup2(nsfd,1);
				execl("./s1",NULL,NULL);
				
			}
					
			else
				close(nsfd);
			tv.tv_sec=10;
			tv.tv_usec=0;
			FD_CLR(sfd[i],&rd);
		}
		if(FD_ISSET(usfd[i],&rd))	
		{			
			
			int k=fork();
			if(k==0)
			{
				char buf[100];
				recvfrom(usfd[i],buf,100,0,(struct sockaddr*)&client1,&length);
				printf("msg received from %d in udp is %s\n",i,buf);
				
			}
			tv.tv_sec=10;
			tv.tv_usec=0;		
			FD_CLR(usfd[i],&rd);
		}
		else
                {
			printf("NO DATA AVAILABLE in recent 10 seconds\n");
                  	tv.tv_sec = 10;
                  	tv.tv_usec = 0;
		}
	}
	
	}
	return 0;
}
	
