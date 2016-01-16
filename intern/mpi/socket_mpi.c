//  network progam using socket and mpi.........

#include<stdio.h>
#include<sys/socket.h>
#include<net/inet.h>
#include<netdb.h>
#include<mpi.h>
#include<string.h>
#include<pthread.h>

int main(int argc,char ***argv)
{
int rank,size,sfd,nsfd;
MPI_Init(&argc,argv);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD,&size);

if(size<2)
{
if(rank==0)
printf("\n pls use atleast 2 process.........\n");
MPI_Finalize();
exit(0);
}

if(rank==0)
{

sfd=socket(AF_INET,SOCK_STREAM,0);
struct sockaddr_in server,client;
bind(sfd,(struct sockaddr*)&server,sizeof(server));
listen(5);
int length;
while(1)
{
nsfd=accept(sfd,(struct sockaddr*)&client,&length);


}



}


else
{



}



return 0;
}
