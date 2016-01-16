#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/wait.h>

int tokenval=13;
int fd1[5][2];
int fd2[5][2];
int Score[5]={0,0,0,0,0};

int main()
{
	int i=0;
	for(i=0;i<5;i++)
	{
		pipe(fd1[i]);
		pipe(fd2[i]);
	}
	for(i=0;i<5;i++)
	{
		int c=fork();
		if(c==0)
		{
			close(fd1[i][0]);
			close(fd2[i][1]);
			dup2(fd1[i][1],1);
	
			dup2(fd2[i][0],0);
			execl("p",NULL);
		}
		else
		{
			close(fd1[i][1]);
			close(fd2[i][0]);
		}
	}
	int Value=9;
	int index=0;
	while(1)
	{
		char val[256]; 
		strcpy(val,""); 
		sprintf(val,"%d",Value); 
		printf("value is %d\n",Value);
		write(fd2[index][1],val,strlen(val)); 
		printf("wrote %s\n",val);
		char buf[256];
		read(fd1[index][0],buf,strlen(buf)); 
		printf("read %s\n",buf);
		Value=atoi(buf);
		if(Value==1)
		{ 
		Score[index]++;
		break;
		}
		index=(index+1)%4;
	}
}
