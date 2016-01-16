#include<stdio.h>
#include<omp.h>
#include<mpi.h>
#include<string.h>
main(int argc,char *argv[])
{
int Numprocs,MyRank,iam;
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&MyRank);
MPI_Comm_size(MPI_COMM_WORLD,&Numprocs);
omp_set_num_threads(atoi(argv[1]));
#pragma omp parallel private(iam)
{
iam=omp_get_thread_num();
if(MyRank%2==0)
{
printf("\n\nhello world is printed by process\t %d and thread id \t%d\n\n",MyRank,iam);
}
}
MPI_Finalize();
}
