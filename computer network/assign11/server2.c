#include<stdio.h>
#include<sys/un.h>
#include<stddef.h>

#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<arpa/inet.h>

#include<unistd.h>
#include<string.h>
#include<strings.h>
#include<stdlib.h>
#include<poll.h>
#include<sys/stat.h>
#include<sys/select.h>
#include<signal.h>
#include<fcntl.h>

#define  SERVERPATH  "some"
#define CLIENT     "3yxvw"
#define MAX 1024
int ffd ,servpid;

int recv_fd(int sfd)
{
	struct msghdr msg;
	//struct cmsgcred  cred;
        //struct cmsgcred *credptr = &cred; 
	struct iovec io;
	char ptr[1];
	io.iov_base = ptr;
	io.iov_len = 1;
	msg.msg_name = 0;
	msg.msg_namelen = 0;
	msg.msg_iov = &io;
	msg.msg_iovlen = 1;

	
	char buf[CMSG_SPACE(sizeof(int))];
	msg.msg_control = buf;
	msg.msg_controllen = sizeof(buf);
printf("ram\n");

	if((recvmsg( sfd, &msg, 0))==-1)
	{
		
		perror("recv\n");
		exit(1);
	}
	printf("ram\n");

	struct cmsghdr *cm;
	cm =  CMSG_FIRSTHDR(&msg);

        //cmredptr =(struct cmsghdr *) buf;
        
	if(cm->cmsg_type != SCM_RIGHTS)
	{
		
		perror("unknown type..\n");
		exit(1);
	}  
printf("ram\n");

	if(cm->cmsg_level != SOL_SOCKET)
	{
		
		perror("unknown LEVEL.\n");
		exit(1);
	}  
	
        
	 printf("received fd:%d\n", *(int*)CMSG_DATA(cm));
	 return *(int*)CMSG_DATA(cm);
}	


void sig_fun( )
{
     int  rsfd =ffd;
          printf("\n signal caught \n");
         int i;
             char sbuff[5];
             read(rsfd,sbuff,5);
             printf("\n %sread : ",sbuff);
kill(servpid,SIGUSR1);
               sleep(2);
            
  
} 	 		

int main()
{signal(SIGUSR1,sig_fun);
  char buff[100];
   int  usfd , rsfd ,len,l; 
    char id[10];
    int current =0 ,next =0;
  struct sockaddr_un   uclntaddr , uservaddr ; 
  unlink(CLIENT);
     if(  (usfd = socket( AF_LOCAL , SOCK_STREAM , 0) ) <0)
               perror("socket error \n");
     uclntaddr.sun_family = AF_UNIX ;
     sprintf(id,"%d",getpid() );
      printf("id  = %d ",getpid());
     strcpy(uclntaddr.sun_path , CLIENT );
      strcat(uclntaddr.sun_path ,id);
    printf("client path is %s\n",uclntaddr.sun_path);

    len =  offsetof(struct sockaddr_un , sun_path ) + sizeof(uclntaddr.sun_path);    
    
  if(bind (  usfd ,(struct sockaddr *) & uclntaddr , len ) <0)
       {perror("bind error  \n");exit(1);}
  
          uservaddr.sun_family = AF_UNIX ;
          strcpy( uservaddr.sun_path , SERVERPATH ); 
    len =  offsetof(struct sockaddr_un , sun_path ) + sizeof(SERVERPATH);  

        if(connect(usfd , (struct sockaddr *) &uservaddr ,len ) <0)
            perror("CONNECT ERRRO \n");
     printf("\n connected succesfully \n");
        l=read(usfd , buff, MAX );
           buff[l] ='\0';
        servpid = atoi(buff);
        printf("\n\n server id =%d\n\n",servpid);
      if( (rsfd=recv_fd(usfd) )== -1)
              { perror("unable to recieve fd \n");exit(1);}

         else
             printf(" fd recieved  %d \n",rsfd);
             printf(" start reading from this file  \n");
        kill(SIGUSR1,servpid);  
           
    
          
return 0;  
}
