#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include <unistd.h>
 
int main(int argc,char* argv[])
{
	    struct sockaddr_in npin;
	    int sfd= socket(AF_INET,SOCK_STREAM,0);
	    int csfd= socket(AF_INET,SOCK_STREAM,0);
	    memset(&npin, 0, sizeof(npin));
	    npin.sin_family = AF_INET;
	    npin.sin_addr.s_addr = INADDR_ANY;
	    npin.sin_port = htons(2123);
	    if (bind(csfd, (struct sockaddr *) &npin, sizeof(npin)) == -1) 
	    {
		perror("bind");
		exit(1);
	    }
	    if (listen(csfd, 5) == -1) 
	    {
		perror("listen");
		exit(1);
	    }
	    struct hostent* hp;
	    struct   sockaddr_in pin; 
	    struct sockaddr_in sin;
	    if(sfd==-1)
	    {
	    perror("socket failed");
	    }
	    int portno=atoi(argv[1]);   
	    hp=gethostbyname("localhost");
	    memset(&pin, 0, sizeof(pin));
	    pin.sin_family = AF_INET;
	    pin.sin_addr.s_addr = ((struct in_addr *)(hp->h_addr))->s_addr;
	    pin.sin_port = htons(portno);
	    
            if(connect(sfd,(struct sockaddr *)&pin,sizeof(pin))==-1)
	    {
		 perror("connect error");
	    }
 
	 char buff[20];
	 recv(sfd,buff,sizeof(buff),0);
	 printf("%s\n",buff);
	 bzero(buff,20);
	 scanf("%s",buff);
	 send(sfd,buff,sizeof(buff),0);
	 strcpy(buff,"2123");
	 send(sfd,buff,sizeof(buff),0);
	 socklen_t addrlen=sizeof(pin);
	 while(1)
	 {
		int nsfd=accept(csfd,(struct sockaddr *)&sin,&addrlen); 
		 if(nsfd==-1)
		 {
			 perror("connection error");
			 exit(1);
		 }
		 if(fork()==0)
		 {
			 close(sfd);
			 char buf[20];
			 recv(nsfd,buf,sizeof(buf),0);
			 printf("%s",buf);
			 break;
		 }
		 close(nsfd);
	 }
 }

