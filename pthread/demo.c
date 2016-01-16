#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
pthread_mutex_t lock;
void *run(void *arg)
{
pthread_mutex_lock(&lock);
int i=*(int*)arg;
printf("\n Thread %d is running\n",i);
int  a=10;
pthread_mutex_unlock(&lock);
return (void *)a;

}

int main()
{

pthread_t t[10];
pthread_mutex_init(&lock,NULL);
int i;
void *status;
for(i=0;i<10;i++)
{pthread_create(&t[i],NULL,run,&i);
//sleep(1);
}
for(i=0;i<10;i++)
{pthread_join(t[i],&status);
printf(" The Thread Said %d\n",(int)status);
}
return 0;
}
