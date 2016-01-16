

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
int *z=(int *)malloc(12);
z=(int*)arg;
int i=z[0];
int j=z[1];
int k=z[2];
int sum=0;
int offsetc=nCols/nThread;
int l;
printf("\n i j and k value is %d %d %d \n",i,j,k*offsetc+l);
printf("\n offset is %d\n",offsetc);
//pthread_mutex_lock(&lock);
//for(l=0;l<offsetc;l++)
//printf("\n i j and k value is %d %d %d \n",i,j,k*offsetc+l);
//sum+=MatrixA[i][offset*nThread+k]*MatrixB[offset*nThread+k][j];
//printf("\n  sum %d \n",sum);
//pthread_mutex_unlock(&lock);
//while(1);
pthread_exit(NULL);



}

void * ColMultiply(void *arg)
{
int * y=(int *)malloc(8);
y=(int *)arg;
int i=y[0];
int j=y[1];
int k,l;


/*calculationthread=(pthread_t *)malloc(sizeof(pthread_t)*nThread);
if(calculationthread==NULL)
{

printf("\n Malloc Error \n");
exit(1);
}
for(k=0;k<nThread;k++)
{
int *x=(int*)malloc(12);
x[0]=i;
x[1]=j*nThread+k;
x[2]=k;
pthread_create(&calculationthread[k],NULL,MultiplyandAdd,(void *)x);

}*/
//printf("\n i and j value is %d%d \n",i,j*nThread+k);
//pthread_mutex_lock(&lock);
int sum=0;
for(k=0;k<nThread;k++)
{sum=0;
for(l=0;l<nCols;l++)
sum+=MatrixA[i][l]*MatrixB[l][j*nThread+k];
MatrixC[i][j*nThread+k]=sum;
}
//printf("\ni and  j vale is%d %d\n",i,j*nThread+k);

//pthread_mutex_unlock(&lock);
/*int sum=0,status=0;
for(k=0;k<nThread;k++)
{
pthread_join(calculationthread[k],(void *)&status);
printf("\n ))))))))))\n");
pthread_mutex_lock(&lock);
//sum+=status;
printf("\n the Sum is %d \n",sum);
MatrixC[i][j*nThread+k]=sum;
pthread_mutex_unlock(&lock);
}*/

//pthread_exit(0);
}

void * RowMultiply(void *arg)
{
int i=*(int*)arg;
int j,k;
offsetR=nRows/nThread;
colthread=(pthread_t*)malloc(sizeof(pthread_t)*offsetR*offsetR);
if(colthread==(void *)-1)
{
perror("Malloc\n");
exit(1);
}
for(k=0;k<offsetR;k++)
{
for(j=0;j<offsetR;j++)
{
int *x=(int*)malloc(8);
x[0]=i*offsetR+k;
x[1]=j;
pthread_create(&colthread[j],NULL,ColMultiply,(void *)x);
}
}
for(k=0;k<offsetR;k++)
{
for(j=0;j<offsetR;j++)
pthread_join(colthread[j],NULL);
}
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
//printf_matrix(MatrixA,nRows,nCols);
//printf_matrix(MatrixB,nRows,nCols);
//printf("\n  starting ---------------\n");
for(i=0;i<nThread;i++)
{
int *a=(int*)malloc(sizeof(int));
*a=i;
pthread_create(&rowthread[i],NULL,RowMultiply,(void *)a);

}
for(i=0;i<nThread;i++)
pthread_join(rowthread[i],NULL);

printf_matrix(MatrixC,nRows,nRows);
free(MatrixA);
free(MatrixB);
free(MatrixC);
return 0;
}

                                                                                                               
