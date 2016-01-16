/*  matrix multiplication using pthread  
Aim: matrix multiplication using pthread*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<pthread.h>
#include<errno.h>
int sum=0;
pthread_mutex_t lock;

pthread_t *rowthread,*colthread,*calculationthread;
int nRows,nCols,nThread;
int **MatrixA,**MatrixB,**MatrixC;
int offsetR,offsetC; 

/*
void * ColMultiply(void *arg)
{
int y;
//scanf("\nin ColMultiply Function %d\n",&y);
int *a=(int *)arg;
int i=*a;
int j=*(++a);
//offsetC=nCols/nThread;

int k;
struct identification
{

int a,b,c;
}id;

for(k=0;k<nThread;k++)
{
pthread_mutex_lock(&lock);
int sum=0,l=0;
for(l=0;l<nCols;l++)
sum+=MatrixA[i][l]*MatrixB[l][j*nThread+k];
MatrixC[i][j*nThread+k]=sum;
printf("\n j vale is %d\n",j*nThread+k);

pthread_mutex_lock(&lock);}

}
*/
void * RowMultiply(void *arg)
{
int i=*(int*)arg;
int j;
struct identity
{
int a;
int b;

}id;
offsetR=nRows/nThread;
colthread=(pthread_t*)malloc(sizeof(pthread_t)*offsetR);
if(colthread==(void *)-1)
{
perror("Malloc\n");
exit(1);
}
for(j=0;j<offsetR;j++)
{
//printf("\n %d\n",i*offsetR+j);
int k,l;
for(k=0;k<nRows;k++)
{
int sum=0;
for(l=0;l<nCols;l++)
sum+=MatrixA[i*offsetR+j][l]*MatrixB[l][k];
MatrixC[i*offsetR+j][k]+=sum;

}
}
//sleep(1);
}
void fillMatrix(int **a,int row,int col)
{
int i,j;
for(i=0;i<row;i++)
{
for(j=0;j<col;j++)
{
a[i][j]=2;

}
}
}

printf_matrix(int **a,int row ,int col)
{

int i, j;
for(i=0;i<row;i++)
{
for(j=0;j<col;j++)
{
printf("%d ",a[i][j]);
}
printf("\n");
}
}
int main(int argc,char *argv[])
{
pthread_mutex_init(&lock,NULL);
if(argc==1)
{
nRows=nCols=1000;
nThread=100;
}
if(argc==2)
{
nRows=nCols=atoi(argv[1]);
nThread=100;
}

if(argc==4)
{
nRows=atoi(argv[1]);
nCols=atoi(argv[2]);
nThread=atoi(argv[3]);
}
int i,j,k;
MatrixA=(int **)malloc(sizeof(int*)*nRows);
for(i=0;i<nRows;i++)
MatrixA[i]=(int *)malloc(sizeof(int)*nCols);
MatrixB=(int **)malloc(sizeof(int*)*nCols);
for(i=0;i<nCols;i++)
MatrixB[i]=(int *)malloc(sizeof(int)*nRows);
MatrixC=(int **)malloc(sizeof(int*)*nRows);
for(i=0;i<nRows;i++)
MatrixC[i]=(int *)malloc(sizeof(int)*nRows);
fillMatrix(MatrixA,nRows,nCols);
fillMatrix(MatrixB,nCols,nRows);
rowthread=(pthread_t*)malloc(sizeof(pthread_t)*nThread);
//colthread=(pthread_t*)malloc(sizeof(pthread_t)*nThread);
//calculationthread=(pthread_t*)malloc(sizeof(pthread_t)*nThread);
//printf_matrix(MatrixA,nRows,nCols);
//printf_matrix(MatrixB,nCols,nRows);
struct timeval tv_start,tv_end;
gettimeofday(&tv_start,NULL);
for(i=0;i<nThread;i++)
{
int *tid;
tid=(int *)malloc(sizeof(int));
*tid=i;
int a=pthread_create(&rowthread[i],NULL,RowMultiply,(void *)tid);
if(a!=0)
{

printf("Thread Creation Error..\n");exit(1);
}
}
for(i=0;i<nThread;i++)
pthread_join(rowthread[i],NULL);
gettimeofday(&tv_end,NULL);
double time_parallel=(tv_end.tv_sec-tv_start.tv_sec)+(tv_end.tv_usec-tv_start.tv_usec)/1000000;
//printf_matrix(MatrixC,nRows,nRows);
gettimeofday(&tv_start,NULL);
for(i=0;i<nRows;i++)
{
for(j=0;j<nRows;j++)
{sum=0;
for(k=0;k<nCols;k++)
sum+=MatrixA[i][k]*MatrixB[k][j];
MatrixC[i][j]=sum;
}
}
gettimeofday(&tv_end,NULL);
double time_serial=(tv_end.tv_sec-tv_start.tv_sec)+(tv_end.tv_usec-tv_start.tv_usec)/1000000;
printf("\n Parallel Took %f  sec   while Serial took %f sec\n",time_parallel,time_serial);
free(MatrixA);
free(MatrixB);
free(MatrixC);
return 0;
}

                                                                                                               
