#include<sys/un.h>
#include<stddef.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<strings.h>

#include<sys/socket.h>
#include<netdb.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>
#include<sys/ipc.h>
#include<sys/stat.h>

#include<poll.h>
#include<sys/select.h>
#include<poll.h>
#include<signal.h>

#define  SERVERPATH  "some"

int cpid ,cfd ;

void pass_fd(int sfd, int fd_to_send)
{
	struct msghdr msg;
	
	
	char buf[CMSG_SPACE(sizeof(int))];
	
	
	struct cmsghdr *cmsg;
	
	struct iovec ve;	
	
	char *st ="I";
	
	ve.iov_base = st;
	ve.iov_len =1;
	
	
	msg.msg_iov = &ve;
	msg.msg_iovlen = 1;
	
	msg.msg_name = NULL;
	msg.msg_namelen = 0;
	

	msg.msg_control = buf;
	msg.msg_controllen = sizeof(buf);
	
	cmsg = CMSG_FIRSTHDR(&msg);
	
	
  	cmsg->cmsg_level = SOL_SOCKET;
  	cmsg->cmsg_type = SCM_RIGHTS;
  	cmsg->cmsg_len = CMSG_LEN(sizeof(fd_to_send));
	
	*(int*)CMSG_DATA(cmsg) = fd_to_send;
	
	msg.msg_controllen = cmsg->cmsg_len;
	
	
	msg.msg_flags = 0;
	
	
	if(sendmsg( sfd, &msg, 0)==-1){ perror("snd:\n"); exit(1); }
	
	printf("sent fd:%d\n", fd_to_send);
	//close(fd_to_send);
	
}

void sig_fun( )
{
         
          printf("\n signal caught  from server : - \n");
          int i;
          char sbuff[5];
          read(cfd,sbuff,5);
          printf("\n %sread : ",sbuff);
          sleep(3);
          kill(cpid ,SIGUSR1 );
   
}

#define MAX 1024

int main()
{
char c;
   char buff[MAX];
   int current , next;
 int usfd ,unsfd  ,tmpfd ,clientpid ;
   socklen_t len;
   struct sockaddr_un  uservaddr ,utemp ;
  printf("\n pid = %d \n" ,getpid());
  if( ( usfd= socket( AF_UNIX ,  SOCK_STREAM , 0)) < 0)
        perror(" socket error \n");

    bzero(&uservaddr , sizeof(struct sockaddr_un) );
    uservaddr.sun_family = AF_UNIX ;
    
    unlink(SERVERPATH);
    strncpy( uservaddr.sun_path , SERVERPATH , sizeof( uservaddr.sun_path) -1 );
    
    len =  offsetof(struct sockaddr_un ,sun_path) + strlen( uservaddr.sun_path) ;

if( bind( usfd , (struct sockaddr *) & uservaddr , len ) <0)
    perror("socket erorr ");
      len =sizeof(struct sockaddr_un );
        getsockname( usfd , (struct sockaddr * ) &utemp , &len );

 printf(" sfd = %d name = %s , returned len  = %d\n",usfd ,  utemp.sun_path , len);
  listen(usfd , 5);
     
     bzero(&utemp ,sizeof(utemp));
     len = 108;
        printf("\n WAITING FOR CLIENT \n");
       if(  (unsfd = accept( usfd , (struct sockaddr *) &utemp , &len) ) <0)
            printf("accept error \n");
               printf(" usfd %dand nsfd = %d  and path = %s ",usfd ,unsfd ,utemp.sun_path );
               strcpy(buff , utemp.sun_path);
             printf("\n\n path is%s \n", &buff[strlen(buff)-4] );

 clientpid = atoi(&buff[strlen(buff)-4]);
          int l;
          
             close(usfd);
      signal(SIGUSR1 , (void*)sig_fun);
      printf("\n\n\nclientpid = %d \n",clientpid);
      cpid = clientpid;
            sprintf(buff,"%d",getpid());
                 write(unsfd,buff,strlen(buff));

if((tmpfd = open( "in.txt" , 0666)) <0 )
                            {perror("unable to open requeste d file \n");exit(1);}
                      printf(" opened file succesfully  tmp fd = %d  \n" , tmpfd );
                      cfd = tmpfd; 
                      pass_fd(unsfd,tmpfd);
        printf("fd sent \n");
read( tmpfd , buff , 10);
                lseek(tmpfd,10,SEEK_CUR);

while(1);

return 0;
}


