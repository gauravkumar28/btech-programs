#include<stdio.h>
#include<unistd.h>
#include<sys/time.h>
#include<sys/types.h>
#include<sys/select.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<fcntl.h>
#include<stdlib.h>
#include<pthread.h>
void *rd_service(void *arg)
{
	printf("thread\n");
	char buf[100];
	int nsfd=*(int *)arg;
	//while(1)
	//{
	recv(nsfd,buf,100,0);
	printf("msg rcvd is:%s\n",buf);
	gets(buf);
	send(nsfd,buf,100,0);
	//}
}
int usfd[5];
char buf1[100];
void *udp_service(void *arg)
{
	int udp=*(int *)arg;
	struct sockaddr_in client1;
	int length1;
	recvfrom(udp,buf1,100,0,(struct sockaddr*)&client1,&length1);
				printf("msg received from in udp is %s\n",buf1);
	gets(buf1);
	sendto(udp,buf1,100,0,(struct sockaddr*)&client1,sizeof(client1));
}
int main()
{
	int i,j,sfd[5];
	struct sockaddr_in server,client,server1;
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
			pthread_t p;
			for(j=0;j<5;j++)
					close(sfd[j]);
			pthread_create(&p,NULL,&rd_service,(void *)&nsfd);
			pthread_join(p,NULL);
		
			
			tv.tv_sec=10;
			tv.tv_usec=0;
			FD_CLR(sfd[i],&rd);
		}
		if(FD_ISSET(usfd[i],&rd))	
		{			
			
			int k=fork();
			if(k==0)
			{
				pthread_t p;
				char buf[100];
				pthread_create(&p,NULL,&udp_service,(void *)&usfd[i]);
				pthread_join(p,NULL);
				
			}
			tv.tv_sec=10;
			tv.tv_usec=0;		
			FD_CLR(usfd[i],&rd);
		}
		/*else
                {
			printf("NO DATA AVAILABLE in recent 10 seconds\n");
                  	tv.tv_sec = 10;
                  	tv.tv_usec = 0;
		}*/
	}
	
	}
	return 0;
}
	
