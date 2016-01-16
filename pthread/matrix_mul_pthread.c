/* Aim: Matrix Multiplication Using Pthread Too See the performaince difference
Input: matrix A,Matrix B,Matrix C,nRows,nCols,nThread;
Output: Resultent matrix C and Time Analysis
Assumption: nRows and nCols is multiple of nThread
*/

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


void * MultiplyandAdd(void *arg)
{
//printf("\n  sum is \n");
int sum=0;
int *a=(int *)arg;
int i=*a;
int j=*++a;
int offset=*++a;
int offsetc=nCols/nThread;
int k;
pthread_mutex_lock(&lock);
for(k=0;k<offsetc;k++)
sum+=MatrixA[i][offset*nThread+k]*MatrixB[offset*nThread+k][j];
printf("\n  sum %d \n",sum);
pthread_mutex_unlock(&lock);
//while(1);
pthread_exit(&sum);



}

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
calculationthread=(pthread_t *)malloc(sizeof(pthread_t)*nThread);
if(calculationthread==NULL)
{

printf("\n Malloc Error \n");
exit(1);
}
for(k=0;k<nThread;k++)
{
id.a=i;
id.b=j*nThread+k;
id.c=k;
int x=pthread_create(&calculationthread[k],NULL,MultiplyandAdd,&id);
if(x!=0)
{
printf("\n Pthread_Creat Error \n");
exit(1);
}
}
int sum=0,status=0;
for(k=0;k<nThread;k++)
{
pthread_join(calculationthread[k],(void *)&status);
printf("\n ))))))))))\n");
pthread_mutex_lock(&lock);
//sum+=status;
printf("\n the Sum is %d \n",sum);
MatrixC[i][j*nThread+k]=sum;
pthread_mutex_unlock(&lock);
}
//while(1);
}

void * RowMultiply(void *arg)
{
int i=*(int*)arg;
printf("\n %d \n",i);
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
id.a=i*offsetR+j;
id.b=j;
int x=pthread_create(&colthread[i],NULL,ColMultiply,&id);
if(x!=0)
{
perror("Thread not Created \n");
exit(1);
}

}
while(1);
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
int i,j;
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
printf_matrix(MatrixA,nRows,nCols);
printf_matrix(MatrixB,nRows,nCols);
//printf("\n  starting ---------------\n");
for(i=0;i<nThread;i++)
{
printf("\n created ---\n");
int a=pthread_create(&rowthread[i],NULL,RowMultiply,&i);
if(a!=0)
{

printf("Thread Creation Error..\n");exit(1);
}
}
for(i=0;i<nThread;i++)
pthread_join(rowthread[i],NULL);

printf_matrix(MatrixC,nRows,nRows);
free(MatrixA);
free(MatrixB);
free(MatrixC);
return 0;
}
