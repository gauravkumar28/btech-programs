#include<stdio.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<unistd.h>
#include<signal.h>
#include<string.h>
#include<fcntl.h>
#include<sys/wait.h>
#define num 3
#define maxpoint 20

long pids[num];
int fd[num][2];
int points[num]={0};

void handle(int signo)
{       
	if(signo==SIGUSR1)
	{                     
		exit(0);
	}  
}

main()
{

    long pid;
    int tmp = 0,j;

    for(j=0;j<num;j++)
    {
    	if(pipe(fd[j])==-1)
        	printf("error to open the pipe:\n"); 
	}
	while(tmp < num) 
    {
		pid = fork();	
		if(pid>0)
        {
			pids[tmp] = pid;
			tmp++;
		}
		else if (pid == 0)
		{
			signal(SIGUSR1,handle);
			int n;
			char buf[50];
		    while(1)
            {
		    	 memset(buf,0,sizeof(buf));
           	     if(read(fd[tmp][0],buf,50)==-1)
                     printf("error in reading\n");
				 printf("buf 2: %s\n",buf);
			 	 n = atoi(buf);
			 	 memset(buf,0,sizeof(buf));
			 	 n=n-1;    
			 	 sprintf(buf,"%d",n);
             	 if(write(fd[tmp][1],buf,50)==-1)
                 	printf("error in writing\n");
			     printf("buf 2: %s\n",buf);
			 	 memset(buf,0,sizeof(buf));
			     sleep(3);
           }
		}
	}
    int token,i=0;
    char buf[50];
    while (1)
	{ 
		token = (rand()%3)+1;
		printf("token is : %d\n",token);
		while (token !=0)
		{
			if(i==num)
				i=0;
			memset(buf,0,sizeof(buf));
			sprintf(buf,"%d",token);
            if(write(fd[i][1],buf,50)==-1)
                 printf("error in writing\n");
			printf("buf 1: %s\n",buf);
			memset(buf,0,sizeof(buf));
			sleep(2);	
            if(read(fd[i][0],buf,50)==-1)
                        printf("error in reading\n");
			printf("buf 1: %s\n",buf);
			token = atoi(buf);
			memset(buf,0,sizeof(buf));	
			i++;
		}
		i--;
		points[i] = points[i]+5;
		printf("points of %d is : %d \n",i,points[i]);
		if(points[i] == maxpoint)
			{	printf("winner is : %d \n",i);break; } 
	}
	for(j=0; j<num && j!=i; j++)
         kill(pids[j],SIGUSR1);	
	while(1);
}
