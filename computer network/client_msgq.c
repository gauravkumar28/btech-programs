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
m.mtype=1;

int msqid;
msqid=msgget(1238,0666|IPC_CREAT);
printf("\n %d",msqid);
while(1)
{m.mtype=1;
printf("\n messege\t");
gets(m.mtext);
msgsnd(msqid,&m,sizeof(m)-sizeof(m.mtype),0);
//sleep(2);
m.mtype=2;
msgrcv(msqid,&m,sizeof(m)-sizeof(m.mtype),2,0);
printf("\n server says:%s",m.mtext);


}

return 0;
}
