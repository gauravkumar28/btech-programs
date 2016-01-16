#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<mpi.h>

int main(int argc,char ***argv)
{
int size,rank,err,i,source_id;
MPI_Status status;
char msg[100];
const int tag=100;
err=MPI_Init(&argc,argv);
if(err!=MPI_SUCCESS)
{
printf("\n init error");exit(0);
}
err=MPI_Comm_size(MPI_COMM_WORLD,&size);
if(err!=MPI_SUCCESS)
{
printf("\n size error ");exit(0);
}
err=MPI_Comm_rank(MPI_COMM_WORLD,&rank);
if(err!=MPI_SUCCESS)
{
printf("\n rank error ");exit(0);
}
if(size<2)
{


printf("\n you need two process two run this.....");
MPI_Finalize();
exit(0);
}
if(rank==0)
{
int length;
MPI_Get_processor_name(msg,&length);
printf("\n hello world from processor %d having name %s",rank,msg);
for(i=1;i<size;i++)
{err=MPI_Recv(msg,strlen(msg),MPI_CHAR,i,tag,MPI_COMM_WORLD,&status);
if(err!=MPI_SUCCESS)
{printf("mpi_recv error");
exit(0);
}
source_id=status.MPI_SOURCE;
printf("\n%s from process %d",msg,source_id);
}
}
else
{
memset(msg,0,100);
gets(msg);
err=MPI_Send(msg,strlen(msg),MPI_CHAR,0,tag,MPI_COMM_WORLD);
if(err!=MPI_SUCCESS)
{

printf("mpi_send error");exit(1);
}
}
MPI_Finalize();
if(rank==0)
printf("\n--------------ready");
return 0;
}
