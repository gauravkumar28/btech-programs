#include<stdio.h>
#include<stdlib.h>
#include <mpi.h>
#include<string.h>
int main(int argc ,char ***argv)
{
struct msg
{
int length;
char msg[100];

};
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
struct msg m;
if(rank==0)
{
gets(m.msg);
MPI_Send(&m,sizeof(m),MPI_BYTE,1,tag,MPI_COMM_WORLD);
//MPI_Recv(msg,strlen(msg),MPI_CHAR,1,tag,MPI_COMM_WORLD,&status);
//printf("process ------says %s",msg);

}
else if(rank==1)
{
MPI_Recv(&m,sizeof(m),MPI_BYTE,0,tag,MPI_COMM_WORLD,&status);
printf("process ------says %s",m.msg);

}
MPI_Finalize();
return 0;
}
