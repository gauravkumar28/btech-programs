#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/select.h>

 int sd[5],i,len,bi,nsd,port,j;
 char content[30];
struct sockaddr_in ser[5],cli[5];
pthread_t p[15];
fd_set rset;
int fd[2];
void *pro(void *n)
{
    char msg[40];
     FD_ZERO(&rset);
     int max=8;
    int m;
    char buf[30];
    while(1)
    {
        for(m=0;m<5;m++)
        FD_SET(sd[m],&rset);
        select(max,&rset,NULL,NULL,NULL);
       for(i=0;i<5;i++)
       {
           // printf("pk\n");
            if(FD_ISSET(sd[i],&rset))
            {
                //printf("waiting for connection\n");
                if(fork()==0)
                {
                    nsd = accept(sd[i],((struct sockaddr *)&cli[i]),&j);
                    if(nsd==-1)
                    {
                    //    printf("\nCheck the description parameter\n");
                        return 0;
                    } 
                    else
                    {
                        printf("\nConnection accepted through tcp\n");
                        int pid = fork();
                        if(pid==0)
                        {
                            close(sd[i]);
                            content[0]=i+48+1;
                            content[1]=0;
                            dup2(nsd,100);
                            execl(content,NULL,NULL);
                        }
                        FD_CLR(sd[i],&rset);
                    } 
                }
		/*
                else
                {
                   // printf("Connection accepted through udp\n");
                    //while(1)
                    {
                    if(fork()==0)
                    {
                        close(sd[i]);
                        content[0]=i+48+1;
                        content[1]='\0';
                        //dup2(fd[1],1);
                        //dup2
                        //recvfrom(sd[i],msg,20,0,(struct sockaddr *)&cli[i],&j);
                        //dup2(,100);
                        
                        //printf("%s",msg);
                        if(fork()==0)
                        execl(content,NULL,NULL);
                    }
                    FD_CLR(sd[i],&rset);
                    }
                    
                }*/
            }
        }
    }
}
main()
{
    printf("enter the port\n");
    scanf("%d",&port);
    pipe(fd);
   
    for(i=0;i<3;i++)
    {
        if((sd[i]=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==-1)
        {
            printf("\nSocket problem");
            return 0;
        }
    

        printf("\n tcp Socket created\n");
        bzero((char*)&cli[i],sizeof(ser[i]));
        

        int optval = 1;
        printf("\nPort Address is %d\n:",port);
        ser[i].sin_family=AF_INET;
        ser[i].sin_port=htons(port);
        port++;
        ser[i].sin_addr.s_addr=htonl(INADDR_ANY);    
        setsockopt(sd[i],SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval));
        bi=bind(sd[i],(struct sockaddr *)&ser[i],sizeof(ser[i]));

        if(bi==-1)
        {
            printf("\nBind error\n");
            return 0;
        }

        j=sizeof(cli[i]);
        listen(sd[i],5);
    }   
    for(i=3;i<5;i++)
    {
        if((sd[i]=socket(AF_INET,SOCK_DGRAM,0))==-1)
        {
            printf("\nSocket problem");
            return 0;
        }
        printf("\n udp Socket created\n");
        bzero((char*)&cli[i],sizeof(ser[i]));
        

        int optval = 1;
        printf("\nPort Address is %d\n:",port);
        ser[i].sin_family=AF_INET;
        ser[i].sin_port=htons(port);
        port++;
        ser[i].sin_addr.s_addr=htonl(INADDR_ANY);    
         ser[i].sin_addr.s_addr=htonl(INADDR_ANY);    
        setsockopt(sd[i],SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval));
        bi=bind(sd[i],(struct sockaddr *)&ser[i],sizeof(ser[i]));

        if(bi==-1)
        {
            printf("\nBind error\n");
            return 0;
        }

        j=sizeof(cli[i]);
    
    }
    i=0;
    int k=0,z,j=0;
    while(k<5)
    {
        //printf("pk\n");
        if(fork()==0)
        {
            
               z=i+3;
               for(;i<z;i++)
               pthread_create(&p[i],NULL,pro,NULL);
               for(;j<z;j++)
                pthread_join(p[j],NULL);
		        
        }
        k++;
    }
    return 0;
}
