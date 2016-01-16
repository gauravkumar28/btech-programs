#include<stdio.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/ipc.h>

# define key1 8356
# define key2 2345
struct mymessage
{ 
   long mtype;
   char mtext[512];
   long pid;
   int group;
};

main()
{

int g;
printf("which group?\n");
scanf("%d",&g);
struct mymessage m;
int msgid=msgget(key1,0);
m.pid=getpid();
m.mtype=5;
m.group=g;
msgsnd(msgid,&m,sizeof(m)-sizeof(m.mtype),IPC_NOWAIT);
int c=fork();

while(1)
{
	if(c>0)	
	{
	m.mtype=getpid();
	while(msgrcv(msgid,&m,sizeof(m)-sizeof(m.mtype),m.mtype,IPC_NOWAIT)==-1);
	printf("\n%s\n",m.mtext);
	}
	else
	{
	m.mtype=7;
	printf("enter message\n");
	gets(m.mtext);
	msgsnd(msgid,&m,sizeof(m)-sizeof(m.mtype),IPC_NOWAIT);
	}
}
}
