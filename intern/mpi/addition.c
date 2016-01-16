//  matrix addition...using mpi



#include<stdio.h>
#include<mpi.h>
#include<stdlib.h>
#include<malloc.h>
int main(int argc,char *** argv)
{
MPI_Status status;
int rank,size,length,i,block,offset,a,b;
double sum=0,psum=0;
double *arr;
MPI_Init(&argc,argv);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD,&size);
double start_time=MPI_Wtime();
if(rank==0)
{

printf("\n enter the size of array...\n");
scanf("%d",&length);
if(length<size)
{


printf("\n pls reduce processes and try again...\n");
MPI_Finalize();
exit(0);
}

arr=(double*)malloc(length*sizeof(double));
if(arr==NULL)
{printf("error..\n");
exit(0);
}

for(i=0;i<length;i++)
arr[i]=1;
block=length/(size-1);
offset=length%(size-1);
for(i=1;i<size;i++)

{
a=MPI_Send(&block,1,MPI_INT,i,0,MPI_COMM_WORLD);
if(a!=MPI_SUCCESS)
{
printf("error\n");exit(1);
}
MPI_Send(&arr[block*(i-1)],block,MPI_DOUBLE,i,0,MPI_COMM_WORLD);
//printf("\nmaster sent  %d size block to %d process",block,i);
}
sum=0;
for(i=1;i<size;i++)
{

a=MPI_Recv(&psum,1,MPI_DOUBLE,i,1,MPI_COMM_WORLD,&status);
if(a!=MPI_SUCCESS)
{
printf("recv error\n");
exit(0);
}
sum+=psum;
}
for(i=0;i<offset;i++)
sum+=arr[block*(size-1)+i];
printf("\n-----------the sum of the array is %f",sum);

}

else 
{
b=MPI_Recv(&block,1,MPI_INT,0,0,MPI_COMM_WORLD,&status);
if(b!=MPI_SUCCESS)
{
printf("recv error\n");
}

arr=(double*)malloc(block*sizeof(double));
 b=MPI_Recv(arr,block,MPI_DOUBLE,0,0,MPI_COMM_WORLD,&status);
if(b!=MPI_SUCCESS)
{
printf("recv error\n");
exit(0);
}

sum=0;
for(i=0;i<block;i++)
sum+=arr[i];
MPI_Send(&sum,1,MPI_DOUBLE,0,1,MPI_COMM_WORLD);
}
double end_time=MPI_Wtime();
if(rank==0)
printf("\n time elapsed  is\t%f\n",end_time-start_time);
MPI_Finalize();
return 0;
}
