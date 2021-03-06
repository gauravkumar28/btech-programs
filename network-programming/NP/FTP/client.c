//  FILE DOWNLOADING CLIENT

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<sys/select.h>
#include<netdb.h>
#include<fcntl.h>
#include<sys/stat.h>
#define LISTEN_NO 10
#define no_server 2

int  serverno[no_server] , mark[no_server] , port[no_server] , sfd[no_server];
char  ip[no_server][50]; 
pthread_t tid[100];
int allsfd[100],cntfd=0;
pthread_mutex_t mux;

struct transfer
{
    int fds;
    char filename[50];
    int number;
    int newport;
}ob;

void init()
{
     int i;
     for(i=0;i<no_server;i++)
        { mark[i]=0;sfd[i]=0;} 

    port[0]=7651;port[1]=7652;
    strcpy(ip[0] , "127.0.0.1");
    strcpy(ip[1] , "127.0.0.2");
}

int createnewsocket(int no,int newport)
{
	struct sockaddr_in claddr;
	int tmpsfd;
	tmpsfd=socket(AF_INET,SOCK_STREAM,0);
		perror("socket status : ");

    memset(&claddr,0,sizeof(claddr));

	claddr.sin_family=AF_INET;	
	claddr.sin_port=htons(newport);
	inet_pton(AF_INET,ip[no-1],&claddr.sin_addr);
		  perror("ip status :");

    connect(tmpsfd,(struct sockaddr *)&claddr,sizeof(claddr));
//		perror("connect status :");
    return tmpsfd;
}

void fileservice(void *arg)
{
	struct transfer ob2;int q;char tmp[50];
	ob2=*((struct transfer *)arg);
    char buff[50];
    char buf[22];
    int n,i,cn=0;
	memset(buf,0,sizeof(buf));
	memset(buff,0,sizeof(buff));

   strcpy(tmp,ob2.filename);
   printf("filename is : %s \n",ob2.filename);
   //scanf("%d",&q);


    int newsfd=createnewsocket(ob2.number,ob2.newport);   
	//close(ob2.fds);

  while(1)
  {
     sleep(5);
      n=recv(newsfd,buf,sizeof(buf),0);
      buf[strlen(buf)]='\0';
      if(n>0)
               printf("%s\n",buf);
 	  memset(buf,0,sizeof(buf));
       if(n<0)
           {close(newsfd);break;} 
   }
    pthread_exit(NULL);
}


int createsocket(int no)
{
	struct sockaddr_in claddr;
	int tmpsfd;
	tmpsfd=socket(AF_INET,SOCK_STREAM,0);
		perror("socket status : ");

    memset(&claddr,0,sizeof(claddr));

	claddr.sin_family=AF_INET;	
	claddr.sin_port=htons(port[no-1]);
	inet_pton(AF_INET,ip[no-1],&claddr.sin_addr);
		  perror("ip status :");

    connect(tmpsfd,(struct sockaddr *)&claddr,sizeof(claddr));
//		perror("connect status :");
    return tmpsfd;
}


main()
{
	  init();
      int ans,serverno;
      int  csfd,num,cnt=0,n;
      char  filename[50],buf[50],tmp[50]; 
  while(1) 
    {

		 printf("do you want to close connection : \n");
         scanf("%d",&ans); 
     if(ans!=1)
     {
          printf("enter server no : \n");
          scanf("%d",&num);
          
		  printf("enter file name \n");
          scanf("%s",filename);

         strcpy(ob.filename,filename);          
 
		  strcpy(tmp,filename);
        
         if(mark[num-1]==0)
         { 
              csfd=createsocket(num);
             
			send(csfd,tmp,sizeof(tmp),0);	
            printf("filename is : %s \n",filename);

             memset(buf,0,sizeof(buf));
			 n=recv(csfd,buf,sizeof(buf),0);
           
               if(!strcmp(buf,"let's start"))
			   {
						memset(buf,0,sizeof(buf));
						n=recv(csfd,buf,sizeof(buf),0);
                        printf("port no is : %s \n",buf);
                        ob.newport=atoi(buf);
                        memset(buf,0,sizeof(buf));

			  			sleep(6); 
              
			  			
              			sfd[num-1]=csfd;
          
              			mark[num-1]=1;
                        allsfd[cntfd++]=csfd;
			  		
              
						ob.fds=csfd; 
              			ob.number=num;
	          			pthread_create(&tid[cnt++],NULL,(void *)&fileservice,(void *)&ob);
                }
                else
                        {sleep(4); mark[num-1]=0;close(csfd);}
         }
         else
         {
			  send(sfd[num-1],tmp,sizeof(tmp),0);	
              printf("filename is : %s \n",filename);

              memset(buf,0,sizeof(buf));
			  memset(buf,0,50);
			  n=recv(sfd[num-1],buf,sizeof(buf),0);
             			printf("ankit : %s\n",buf);
     
                if(!strcmp(buf,"let's start"))
			    {
						memset(buf,0,sizeof(buf));
						n=recv(sfd[num-1],buf,sizeof(buf),0);
                        ob.newport=atoi(buf);
                        memset(buf,0,sizeof(buf));
              
						ob.fds=sfd[num-1];
              			ob.number=num;
	          			pthread_create(&tid[cnt++],NULL,(void *)&fileservice,(void *)&ob);
                }
                else
                        {sleep(4);mark[num-1]=0;close(csfd);}
         }
         
      }
      else
      {
					printf("enter server no \n ");	
                       scanf("%d",&serverno);
                    if(sfd[serverno-1]!=0)
					   {
                            strcpy(buf,"close connection");
                            send(sfd[serverno-1],buf,sizeof(buf),0);
                             memset(buf,0,sizeof(buf));
                           close(sfd[serverno-1]);
                             mark[serverno-1]=0; 
 					 }			
       }
    }
     
}


