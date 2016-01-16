#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<poll.h>

struct pollfd pfd[1];

int main()
{
	dup2(pfd[0].fd,0);
	pfd[0].events=POLLIN;
	pfd[0].revents=0;
	while(1)
	{
	        int c=poll(pfd,1,-1);
		if(c)
		{
			char val[2];
			read(0,val,strlen(val));
			int value=atoi(val);
			--value;
			char buf[2];
			sprintf(buf,"%d",value); 
			write(1,buf,strlen(buf));
		}
	}
}
