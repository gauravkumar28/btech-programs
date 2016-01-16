#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>
#include <pthread.h>
int opf;
char req[]="GET http://www.youtube.com/ HTTP/1.1\r\n\r\n";
struct servers
{
	char serv[30];
	double con_time;
	double tra_time;
}Serv[6];	
void display()
{
	system("clear");
	printf("Proxy\t\t\tconnect_time\t\ttransfer_time\tSpeed(bytes/sec)\n");
        int i;
	for(i=0; i< 6; i++)
		printf("%s\t\t%.2f\t\t\t%.2f\t\t%.3f\n",Serv[i].serv, Serv[i].con_time, Serv[i].tra_time, 1400.0/(Serv[i].tra_time+Serv[i].con_time));
}
void* calc(void* arg)
{
	int id=*((int*)arg);
	char buf[100];
	int con,n,sum;
	time_t A,B,C;
	struct sockaddr_in ser;
	while(1)
	{
		con=socket(AF_INET, SOCK_STREAM, 0);
		bzero(&ser, sizeof(ser));
		ser.sin_family=AF_INET;
		ser.sin_port=htons(3128);
		
		inet_pton(AF_INET, Serv[id].serv, &ser.sin_addr);
		time(&A);
		printf("%d sent request..\n", id);
		connect(con, (struct sockaddr*)&ser, sizeof(ser));
		time(&B);
		write(con, req, strlen(req));
		sum=0;
		while((n=read(con, buf,100))>0) sum+=n;
		
		//cin>>num;
		time(&C);
		Serv[id].con_time=difftime(B,A);
		Serv[id].tra_time=difftime(C,B);
		//Serv[id].byte=sum;
		display();
		close(con);
		sleep(3);
	}	
}


		
int main(int argc, char* argv[])
{
	pthread_t g[6];
	strcpy(Serv[0].serv,"172.30.0.13");
	strcpy(Serv[1].serv,"172.30.0.14");
	strcpy(Serv[2].serv,"172.30.0.15");
	strcpy(Serv[3].serv,"172.30.0.16");
	strcpy(Serv[4].serv,"172.30.0.17");
	strcpy(Serv[5].serv,"172.30.0.18");
	opf=open("byt", O_WRONLY);
	int arr[6]={0,1,2,3,4,5};int i;
	for(i=0; i<6; i++)
		pthread_create(&g[i], NULL, &calc, (void*)&arr[i]);
		
	pthread_join(g[0], NULL);	

exit(0);
}
