#include<stdio.h>
#include<omp.h>
#include<mpi.h>
#include<string.h>
#include<pthread.h>
int Numprocs,MyRank,iam;
void *display(void *arg)
{

int *x=(int*)arg;

printf("\n\n hello from process %d ... with thread id %d \n\n",MyRank,*x);

pthread_exit(NULL);
}
main(int argc,char *argv[])
{
pthread_t t1,t2;
int id1=1,id2=2;
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&MyRank);
MPI_Comm_size(MPI_COMM_WORLD,&Numprocs);
pthread_create(&t1,NULL,display,&id1);
pthread_create(&t2,NULL,display,&id2);
pthread_join(t1,NULL);
pthread_join(t1,NULL);
MPI_Finalize();
}
