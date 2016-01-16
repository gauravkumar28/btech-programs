#include<unistd.h>
#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/time.h>
#include<sched.h> /* to set thread affinity */

#define maxsize 1000
int num_iter =10000 ; //default no. of iterations
int num_threads=64; // default no. of threads
int queue_size=maxsize;
int inserted=0,extracted=0;

struct node
{
int data;
struct node* next;
};

// definition of the queue datastructure
typedef struct
{
int contains;
struct node* front;
struct node* rear;
pthread_mutex_t *mutex;
pthread_cond_t *queue_full;
pthread_cond_t *queue_empty;
}queue ;
queue *q;


void queue_init()
{
q=(queue*)malloc(sizeof(queue));
q->front=(struct node*)malloc(sizeof(struct node));
q->front->next=NULL;
q->rear=q->front;
q->mutex=(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
q->contains=0;
return ;
}

void enqueue(double val)
{
struct node *tmp=(struct node *)malloc(sizeof(struct node));
tmp->data=val;
tmp->next=NULL;
q->rear->next=tmp;
q->rear=tmp;
q->contains++;
return;
}


double dequeue()
{
struct node*tmp=q->front;
q->front=q->front->next;
double retval=tmp->data;
q->contains--;
free(tmp);
return retval;
}
void * producer(void *arg)
{
int loopcnt=num_iter;
int *id=(int *)arg;
while(loopcnt)
{
pthread_mutex_lock(q->mutex);
while(q->contains==queue_size-1)

pthread_cond_wait(q->queue_empty,q->mutex);
enqueue(*id);
inserted=1;
loopcnt--;
pthread_cond_signal(q->queue_full);
pthread_mutex_unlock(q->mutex);
printf("Producer : %d inserted.\n",*id);
sleep(2);
}
}


void *consumer (void *arg)
{
int loopcnt=num_iter;
int *id=(int *)arg;
while(loopcnt)
{pthread_mutex_lock(q->mutex);
while(q->contains==0)
pthread_cond_wait(q->queue_full,q->mutex);
dequeue();
extracted=1;
loopcnt--;
pthread_cond_signal(q->queue_empty);
pthread_mutex_unlock(q->mutex);
printf("Consumer : %d extracted.\n",*id);
sleep(2);
}
}
int main(int argc,char **argv)
{
int i;
double timetaken;
struct timeval tv_start,tv_end;
struct timezone tz_start,tz_end;
unsigned long ThreadAffMask;
unsigned int ThreadAffMaskLen=sizeof(ThreadAffMask);
pid_t ProgPid=getpid();
queue_init();
if(argc==2)
{
num_threads=atoi(argv[1]);
}
else if(argc==3)
{
num_threads=atoi(argv[2]);
queue_size=atoi(argv[2]);
}
else if(argc==4)
{
num_threads=atoi(argv[1]);
queue_size=atoi(argv[2]);
ThreadAffMask=atoi(argv[3]);
if(sched_setaffinity(ProgPid,ThreadAffMaskLen,(cpu_set_t *)&ThreadAffMask)==-1)
perror("Error: couldn't set thread affinity mask\n");
}
else
{
printf("Usage : %s <num_threads> <queue_size> <ThreadAffMask>\n Assuming num_threads =64,queue_size=1000 and default thread affinity \n",argv[0]);
}
pthread_t prod_tids[num_threads],cons_tids[num_threads];
q->mutex=(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
pthread_mutex_init(q->mutex,NULL);
q->queue_full=(pthread_cond_t *)malloc(sizeof(pthread_cond_t));
pthread_cond_init(q->queue_full,NULL);
q->queue_empty=(pthread_cond_t *)malloc(sizeof(pthread_cond_t));
pthread_cond_init(q->queue_empty,NULL);
int tid_id[num_threads];
gettimeofday(&tv_start,&tz_start);
for(i=0;i<num_threads;i++)
{
tid_id[i]=i;
if(pthread_create(&prod_tids[i],NULL,producer,(void *)&tid_id[i])==1)
{perror("pthread _ create error \n");
}
}
for(i=0;i<num_threads;i++)
{
if(pthread_create(&cons_tids[i],NULL,consumer,(void *)&tid_id[i])==-1)
perror("pthread_cretae error \n");
}
for(i=0;i<num_threads;i++)
{
pthread_join(prod_tids[i],NULL);
pthread_join(cons_tids[i],NULL);
}
gettimeofday(&tv_end,&tz_end);
timetaken=tv_end.tv_sec*1000000+tv_end.tv_usec-tv_start.tv_sec*1000000-tv_start.tv_usec;
if(argc==4)
{
sched_getaffinity(ProgPid,ThreadAffMaskLen,(cpu_set_t *)&ThreadAffMask);
printf("pid %d 's executed with affinity: %08lx\n",ProgPid,ThreadAffMask);
}
printf("Exaecution time (sec ): %lf",timetaken/1000000);
return 0;
}

