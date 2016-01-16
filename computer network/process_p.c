#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/shm.h>
#include<fcntl.h>
#include<sys/ipc.h>
#include<stdlib.h>
#include<sys/sem.h>

int mutexonx,mutexony;



struct semon
{
int val;
struct semid_ds *buf;
unsigned short *array;
}arg;
void signal(int semid)
{
struct sembuf smop={0,1,0};
semop(semid,&smop,1);
}
void wait(int semid)
{
struct sembuf smop={0,-1,0};
semop(semid,&smop,1);
}

int main()
{key_t shmkey1,shmkey2,semkey1,semkey2;
int mid1,mid2;
int *shared_memoryx,*shared_memoryy;

shmkey1=ftok("/home/gaurav/cn",5);
shmkey2=ftok("/home/gaurav/cn",17);
semkey1=ftok("/home/gaurav/cn",20);
semkey2=ftok("/home/gaurav/cn",45);

if((mid1=shmget(shmkey1,1024,0666|IPC_CREAT))==-1)
{
printf("\n memmry error");
exit(1);}
printf("\n memmory alloted for x havin id.. %d",mid1);
if((mid2=shmget(shmkey2,1024,0666|IPC_CREAT))==-1)
{
printf("\n memmry error");
exit(1);
}

printf("\n memmory alloted for y havin id.. %d",mid2);
if((mutexonx=semget(semkey1,1,0666|IPC_CREAT))==-1)
{printf("\n semaphore error");
exit(1);
}
arg.val=0;
semctl(mutexonx,0,SETVAL,arg);
if((mutexony=semget(semkey2,1,0666|IPC_CREAT))==-1)
{printf("\n semaphore error");
exit(1);
}
arg.val=1;

semctl(mutexony,0,SETVAL,arg);

shared_memoryx=(int*)shmat(mid1,NULL,0);
shared_memoryy=(int*)shmat(mid2,NULL,0);
*shared_memoryy=0;
while(1)
{printf("\n y value");

wait(mutexony);
printf("\t %d",*shared_memoryy);
*shared_memoryx+=1;
signal(mutexonx);
sleep(2);
}

shmdt(shared_memoryx);
shmdt(shared_memoryy);
shmctl(mid1,IPC_RMID,0);
shmctl(mid2,IPC_RMID,0);
return 0;
}








