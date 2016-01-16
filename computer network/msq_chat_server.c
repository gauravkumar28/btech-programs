#include<stdio.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/ipc.h>

# define key1 9234
# define key2 2345
struct mymessage
{ 
   long mtype;
   char mtext[512];
   long pid;
};



int main()
{
struct mymessage m;
long pid[10];
int count=0;
int msgid=msgget(key1,IPC_CREAT|0666);
int i;
char a[50];
while(1)
{
m.mtype=1;
if(msgrcv(msgid,&m,sizeof(m)-sizeof(m.mtype),1,IPC_NOWAIT)>0)
{
pid[count++]=m.pid;
printf("ready to recive message\n");

}
m.mtype=2;

if(msgrcv(msgid,&m,sizeof(m)-sizeof(m.mtype),m.mtype,IPC_NOWAIT)>0)
{ printf("message received\n");

for(i=0;i<count;i++)
{
m.mtype=pid[i];
if(pid[i]!=m.pid)
msgsnd(msgid,&m,sizeof(m)-sizeof(m.mtype),0);

}
}
}
return 0;
}
