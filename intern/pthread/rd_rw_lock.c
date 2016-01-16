#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

pthread_rwlock_t rwlock;
void *rdlockThread(void *arg)
{
int rc;
printf("\n\n Entered thread 1 ,getting read lock \n\n");
rc=pthread_rwlock_rdlock(&rwlock);
//checkResults("pthread_rwlock_rdlock()\n",rc);
printf("\n got the rwlock read lock\n");
sleep(5);
printf("\n unlock the read lock\n");
rc=pthread_rwlock_unlock(&rwlock);
//checkResults("pthread_rwlock_unlock()\n",rc);
return NULL;
}
void *wrlockThread(void *arg)
{
int rc;
printf("\n\n Entered thread2 ,getting write lock \n\n");
rc=pthread_rwlock_wrlock(&rwlock);
//checkResults("pthread_rwlock_wrlcok()\n",rc);
printf("\n Got the rwlock write lock,now unlock\n\n");
rc=pthread_rwlock_unlock(&rwlock);
//checkResults("pthread_wrlock_unlock()\n",rc);
return NULL;
}
int main(int argc,char *argv[])
{
int rc=0;
pthread_t t1,t2;
rc=pthread_rwlock_init(&rwlock,NULL);

rc=pthread_create(&t1,NULL,rdlockThread,NULL);
rc=pthread_create(&t2,NULL,wrlockThread,NULL);
sleep(5);
rc=pthread_join(t1,NULL);
rc=pthread_join(t2,NULL);
return 0;
}
