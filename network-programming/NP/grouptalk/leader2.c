#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/unistd.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<string.h>
#include<poll.h>
#define ip "127.0.0.1"
#define port 2350
#define port2 2351
#define no_prs 2
int sfd[no_prs],cnt_prs =0;
struct pollfd fds[no_prs];

int createsocket()
{
	struct sockaddr_in servaddr;
	int tmpsfd;
	tmpsfd=socket(AF_INET,SOCK_STREAM,0);   // socket()
		perror("socket status : ");

    memset(&servaddr,0,sizeof(servaddr));

	servaddr.sin_family=AF_INET;	
	servaddr.sin_port=htons(port2);
	inet_pton(AF_INET,ip,&servaddr.sin_addr);
		perror("ip :");

	bind(tmpsfd,(struct sockaddr *)&servaddr,sizeof(servaddr));   //bind()
		perror("bind status : ");

    listen(tmpsfd,10);        //listen()
		perror("listen status : ");
	return tmpsfd;
}

main()
{
	int lsfd = createsocket();
    struct sockaddr_in claddr;
    socklen_t l=sizeof(claddr);
	int i,nsfd;

	int csfd = accept(lsfd,(struct sockaddr *)&claddr,&l);
	for(i=0;i<no_prs;i++)
	{
		nsfd=accept(lsfd,(struct sockaddr *)&claddr,&l);
		sfd[cnt_prs++]=nsfd;
	}

	char buf[50],bufr[50];int n,prs,tmp;
if(fork()>0)
{

    for(i=0;i<no_prs;i++)
    {
       fds[i].fd=sfd[i];
	   fds[i].events=POLLIN;		
 	}    
 	
   while(1)
   {
        tmp=poll(fds,no_prs,-1);        
        if(tmp>0)
        {
             for(i=0;i<no_prs;i++)
            {
                if(fds[i].revents)
                {
					recv(fds[i].fd,buf,sizeof(buf),0);
					n = atoi(buf);	
					memset(buf,0,sizeof(buf));	

					recv(fds[i].fd,buf,sizeof(buf),0);
					prs = atoi(buf);	
					memset(buf,0,sizeof(buf));

					recv(fds[i].fd,bufr,sizeof(bufr),0);
		
					if(n==2)
    				{	
						send(sfd[prs-1],bufr,sizeof(bufr),0);
						memset(bufr,0,sizeof(bufr));
					}
					else if(n==1)
					{
						sprintf(buf,"%d",prs);	
						send(csfd,buf,sizeof(buf),0);
						memset(buf,0,sizeof(buf));

						send(csfd,bufr,sizeof(bufr),0);
						memset(bufr,0,sizeof(bufr));	
					}
                }
             }
        }         
   }
}

else
{
	while(1)
	{
		recv(csfd,buf,sizeof(buf),0);
		prs = atoi(buf);	
		memset(buf,0,sizeof(buf));

		recv(csfd,buf,sizeof(buf),0);	

		send(sfd[prs-1],buf,sizeof(buf),0);
		memset(buf,0,sizeof(buf));
	}
}

}
