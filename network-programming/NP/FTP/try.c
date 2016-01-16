#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<sys/select.h>
#include<sys/unistd.h>
#include<netdb.h>
#include<fcntl.h>
#include<sys/stat.h>
#define LISTEN_NO 10
#define port 7651
#define ip "127.0.0.1"

main()
{
	char *filename="file1";
    //char *temp;
    char buf[512],tmp[20],temp[2];
    int n,p,cn=0,i;
	memset(buf,0,sizeof(buf));
                     memset(tmp,0,sizeof(tmp));
                   memset(temp,0,sizeof(temp)); 
   	int fd=open(filename,O_RDONLY | O_CREAT,0666);
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
                        //  strcpy(temp,buf[i++]);
                         strcat(tmp,temp);
                         tmp[strlen(tmp)]='\0';
                         cn++;
                        
                  }
                  printf("tmp array is :  %s\n",tmp);
         
                  cn=0;
            //      send(ob2.fds,tmp,sizeof(tmp),0);
                  memset(tmp,0,sizeof(tmp));
                   memset(temp,0,sizeof(temp)); 
           }
     }
 	 memset(buf,0,sizeof(buf));
   }


