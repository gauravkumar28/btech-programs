#include<stdio.h>
#include<stdlib.h>
#include <mpi.h>
#include<string.h>
int main(int argc ,char ***argv)
{

int np,rank;
int tag=10;
MPI_Status status;
MPI_Init(&argc,argv);
MPI_Comm_size(MPI_COMM_WORLD,&np);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
if(np!=2)
{
if(rank==0)
{printf("\n we need exactly 2 process................");
}

MPI_Finalize();
exit(0);
}

if(rank==0)
{
char msg[100];
gets(msg);
MPI_Send(msg,strlen(msg),MPI_CHAR,1,tag,MPI_COMM_WORLD);
//MPI_Recv(msg,strlen(msg),MPI_CHAR,1,tag,MPI_COMM_WORLD,&status);
//printf("process ------says %s",msg);

}
else if(rank==1)
{char msg2[100];
MPI_Recv(msg2,strlen(msg2),MPI_CHAR,0,tag,MPI_COMM_WORLD,&status);
printf("process ------says %s",msg2);
gets(msg2);
MPI_Send(msg2,strlen(msg2),MPI_CHAR,0,tag,MPI_COMM_WORLD);
}
MPI_Finalize();
return 0;
}
