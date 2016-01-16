#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<ftw.h>
#define DIRSIZE 20
char fname[20];
int search(const char *name, const struct stat *status, int type)
{
printf("%s\n",name);
if(type == FTW_NS)
return 0;

if(type == FTW_F)
{
	if(!strcmp(name,fname))
	{
	printf("found %s",fname);
	return 1;
	}
}
 return 0;
}
void main(int argc,char* argv[])
{
        char     dir[DIRSIZE];  
	int 	 sfd, nsfd;
	socklen_t addrlen;
	struct   sockaddr_in sin;
	struct   sockaddr_in pin;
        struct sockaddr_in npin;
	
	if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) 
	{
		perror("socket");
		exit(1);
	}
        int portno=atoi(argv[1]);

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons(portno);

	if (bind(sfd, (struct sockaddr *) &sin, sizeof(sin)) == -1) 
	{
		perror("bind");
		exit(1);
	}

	if (listen(sfd, 5) == -1) 
	{
		perror("listen");
		exit(1);
	}
	
        addrlen = sizeof(pin); 

while(1)
{
	if((nsfd = accept(sfd, (struct sockaddr *)  &pin, &addrlen))==-1) 
	{
	exit(1);	
	}
	if(fork()==0)
	{
		close(sfd);
		strcpy(dir,"enter file name");
		if (send(nsfd, dir, sizeof(dir),0) == -1) 
		{
			perror("recv");
			exit(1);
		}
	
		bzero(dir,DIRSIZE);
		recv(nsfd,dir,sizeof(dir),0);
		printf("%s\n",dir);
	     
		strcpy(fname,dir);
		bzero(dir,DIRSIZE);
		int res=ftw("xyz",search,10);
		printf("%d\n",res);
		recv(nsfd,dir,sizeof(dir),0);
		int port=atoi(dir);
		printf("%d",port);
		
		int csfd=socket(AF_INET,SOCK_STREAM,0);
		memset(&npin, 0, sizeof(npin));
		npin.sin_family = AF_INET;
		npin.sin_addr.s_addr = INADDR_ANY;
		npin.sin_port = htons(port);
	
		if(connect(csfd,(struct sockaddr *)&npin,sizeof(npin))==-1)
		{
		   perror("connect error");
		}
		
		int fd=open(fname,O_RDONLY);
		char buf[20];
		read(fd,buf,sizeof(buf));
		send(csfd,buf,sizeof(buf),0);
	}
 }
}


 
