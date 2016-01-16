#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/sem.h>
#include<sys/ipc.h>
#include<string.h>
#include<stdlib.h>

#define key 9999
#define key2 8888
struct message
{long mtype;
char mtext[];
int pid;
};
struct server
{
long mtype;
char mtext[];
};

int main()
{

int msgid=semget(key,0666|IPC_CREAT);
if(msgid==-1)
{
printf("\n msg queue error");
exit(1);
}

int pid[10];
int count=0;
int msgid2=semget(key2,0666|IPC_CREAT);
if(msgid2==-1)
{
printf("\n msg queue error");
exit(1);
}
message m;

while(1)
{m.mtype=100;
if(msgrcv(msgid,&m,sizeof(m)-sizeof(long),m.mtype,0)==-1)
{

printf("\n recieve error");
exit(1);
}
else 
pid[count++]=m.pid;
m.mtype=200;
if(msgrcv(msgid,&m,sizeof(m)-sizeof(long),m.mtype,0)>0)
{
for(int i=0;i<count;i++)
if(pid[count]==m.pid)
{

if(msgsnd(msgid,&m,sizeof(m)-sizeof(long),0)==-1)
{
printf("\n send error");
exit(1);
}

}

}
}
return 0;
}
