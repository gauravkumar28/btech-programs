// FILE DOWNLOADING SERVER 2

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
#include<dirent.h>
#define LISTEN_NO 10
#define port 7652
#define ip "127.0.0.2"
#define  direct "/home/ankitpc/NP/programs/FTP"

pthread_t tid[100];
int portno[5]={6591,6592,6593,6594,6595},cntport=0;
pthread_mutex_t mux;

struct transfer
{
     char filename[50];
     int fds;
}ob;

int check(char filename[])
{
	DIR *dp;
	struct dirent *dirp;

    if((dp=opendir(direct))==NULL)
             { printf("cant open %s",direct);return 0;}

	while((dirp=readdir(dp))!=NULL)
		if(!(strcmp(dirp->d_name,filename)));
	     {
                     closedir(dp);
                      return 1;
          }
    closedir(dp);
    return 0;
}

int createnewsocket(int newport)
{
	struct sockaddr_in servaddr;
    struct sockaddr_in claddr; 
    socklen_t l=sizeof(claddr);

	int tmpsfd=socket(AF_INET,SOCK_STREAM,0);
		perror("socket status : ");

    memset(&servaddr,0,sizeof(servaddr));

	servaddr.sin_family=AF_INET;	
	servaddr.sin_port=htons(newport);
	inet_pton(AF_INET,ip,&servaddr.sin_addr);
		perror("ip :");

	bind(tmpsfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
		perror("bind status : ");

    listen(tmpsfd,LISTEN_NO);
		perror("listen status : ");

    int nsfd=accept(tmpsfd,(struct sockaddr *)&claddr,&l);
	
   return nsfd;
}

void fileservice(void *arg)
{
	struct transfer ob2;
	ob2=*((struct transfer *)arg); 

    int newsfd=createnewsocket(ob2.fds);

    char buf[512],tmp[22],temp[2];
    int n,i,cn=0;
	memset(buf,0,sizeof(buf));
    memset(tmp,0,sizeof(tmp));
    memset(temp,0,sizeof(temp)); 

    int fd=open(ob2.filename,O_RDONLY,0666);
	       perror("open status : ");

    n=read(fd,buf,sizeof(buf));
    buf[strlen(buf)]='\0';
     if(n>0)
     {
	       for(i=0;i<strlen(buf);i++)
           {
				  while(cn!=20 && i!=strlen(buf))
                  {
                       temp[0]=buf[i++];
                       temp[1]='\0';
                       strcat(tmp,temp);
                       tmp[strlen(tmp)]='\0';
                       cn++;                        
                  }
                   
        //          printf("tmp array is :  %s\n",tmp);
                  send(newsfd,tmp,sizeof(tmp),0);
                  cn=0;
                  memset(tmp,0,sizeof(tmp));
                  memset(temp,0,sizeof(temp)); 
           }
     }
 	 memset(buf,0,sizeof(buf));
     close(newsfd);
     pthread_exit(NULL);
}

void controlconnect(void *arg)
{
    int newport;char *s;
	int sfds=*((int*)arg);
    char filename[50],buf[50];
    int cnt=0,n;
    while(1)
    {
	      n=recv(sfds,filename,sizeof(filename),0);
       if(strcmp(filename,"close connection"))
       {
          if(n>0)
         {			
                printf("file name is : %s\n",filename);
                if(check(filename))
                {
                      memset(buf,0,sizeof(buf));
                      strcpy(buf,"let's start");
                      send(sfds,buf,sizeof(buf),0);
                      memset(buf,0,sizeof(buf));
   
   	 				pthread_mutex_lock(&mux);
    				newport=portno[cntport++];
    				pthread_mutex_unlock(&mux);
    				s =malloc(sizeof(char *));
    				sprintf(s,"%d",newport);
   					send(sfds,s,sizeof(s),0);  
    				printf("port num is : %s \n",s);
                         
                      strcpy(ob.filename,filename);
                      ob.fds=atoi(s);
                      pthread_create(&tid[cnt++],NULL,(void *)&fileservice,(void *)&ob);
                      memset(filename,0,sizeof(filename));
                } 
                else
                {
                      memset(buf,0,sizeof(buf));
                      strcpy(buf,"close connection");
                      send(sfds,buf,sizeof(buf),0);
					  close(sfds);
                      pthread_exit(NULL);
                }
          }
        }
         else
          {
                  close(sfds);break;
          } 
    }	
}

int createsocket()
{
	struct sockaddr_in servaddr;
	int tmpsfd;
	tmpsfd=socket(AF_INET,SOCK_STREAM,0);
		perror("socket status : ");

    memset(&servaddr,0,sizeof(servaddr));

	servaddr.sin_family=AF_INET;	
	servaddr.sin_port=htons(port);
	inet_pton(AF_INET,ip,&servaddr.sin_addr);
		perror("ip :");

	bind(tmpsfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
		perror("bind status : ");

    listen(tmpsfd,LISTEN_NO);
		perror("listen status : ");
	return tmpsfd;
}

main()
{
      pthread_mutex_init(&mux,NULL);
      int sfd,nsfd;
	  pthread_t tid;
      struct sockaddr_in claddr; 
      sfd=createsocket();
      socklen_t l=sizeof(claddr);

	  while(1)
	  {
		 nsfd=accept(sfd,(struct sockaddr *)&claddr,&l);
		 if(fork()==0)
		 {
			   close(sfd);
		       pthread_create(&tid,NULL,(void *)&controlconnect,(void *)&nsfd);	
               pthread_join(tid,NULL);
		 }
		 else
		 {
			  close(nsfd);
		 }
	  }
}

d);
		 }
	  }
}

