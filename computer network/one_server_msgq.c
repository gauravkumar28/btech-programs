#include<stdio.h>
#include<sys/types.h>
#include<sys/msg.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/ipc.h>

struct msg
{
long mtype;
char mtext[20];
};


int main()
{

struct msg m;
int msqid;
msqid=msgget(1234,0666|IPC_CREAT);
printf("\n %d",msqid);
while(1)
{
m.mtype=1;
while((msgrcv(msqid,&m,sizeof(m)-sizeof(m.mtype),1,0)==-1));
printf("\n client says::%s",m.mtext);
//sleep(2);
printf("\n messege\t");
gets(m.mtext);
m.mtype=2;
while((msgsnd(msqid,&m,sizeof(m)-sizeof(m.mtype),0)==-1));
//sleep(2);
}

return 0;
}
