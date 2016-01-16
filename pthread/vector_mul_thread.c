/* Vector Multiplication using pthread and check system
performance with sequential program
input: two vector
output: time difference in parallel and sequential thread
*/








#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<malloc.h>
#include<string.h>
#include<stdlib.h>


pthread_mutex_t lock;
long long  int *MatrixA,*MatrixB,i,j,k,nRows,nThread,offset;
long long int sum=0;

void * multiply(void *arg)
{
long long int row=*(long long int*)arg;
long long int mysum=0;
int i;
//printf("\n Row is %d\n",row);
for(i=0;i<offset;i++)
mysum=mysum+MatrixA[row*offset+i]*MatrixB[row*offset+i];

pthread_mutex_lock(&lock);
sum=mysum+sum;
printf("\n Row is %d\n",row);

pthread_mutex_unlock(&lock);
pthread_exit(NULL);
}

void fillMatrix(long long int *a,long long int b)
{
for(i=0;i<nRows;i++)
a[i]=b;

}
int main(int argc,char *argv[])
{
pthread_mutex_init(&lock,NULL);
if(argc!=3)
{
printf("\n Pleas Enter The size of The Vector and No Of Thread \n");exit(1);
}
nRows=atoi(argv[1]);

//nRows=1000000000;
nThread=atoi(argv[2]);
pthread_t *t;
MatrixA=(long long int *)malloc(8*nRows);
MatrixB=(long long int *)malloc(8*nRows);
fillMatrix(MatrixA,1);
fillMatrix(MatrixB,2);
t=(pthread_t*)malloc(sizeof(pthread_t)*nThread);
offset=nRows/nThread;
struct timeval tv_start,tv_end;
gettimeofday(&tv_start,NULL);
for(i=0;i<nThread;i++)
{
pthread_create(&t[i],NULL,multiply,&i);

}
for(i=0;i<nThread;i++)
{
pthread_join(t[i],NULL);
}
gettimeofday(&tv_end,NULL);
printf("\n\nThe Result Is :: %d\n",sum);
printf(" \n\nTime Taken in Parallel Code is %f\n",(double)(tv_end.tv_sec-tv_start.tv_sec)+(tv_end.tv_usec-tv_start.tv_usec)/1000000);
sum=0;
gettimeofday(&tv_start,NULL);
for(i=0;i<nRows;i++)
sum+=MatrixA[i]*MatrixB[i];
gettimeofday(&tv_end,NULL);
printf("\n\nThe Result Is :: %d\n",sum);
printf(" \n\nTime Taken in Serial  Code is %f\n",(double)(tv_end.tv_sec-tv_start.tv_sec)+(tv_end.tv_usec-tv_start.tv_usec)/1000000);

return 0;
}
