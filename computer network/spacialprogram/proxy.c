#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<string.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<time.h>
#include<netinet/in.h>
#include<pthread.h>
#include<string.h>
#include<stdlib.h>
char url[]="GET http://www.youtube.com/ HTTP/1.1\r\n\r\n";

struct server
{
char servaddr[30];
double con_time;
double tra_time;

}serv[14];


void display()
{
system("clear");
printf("proxy\t\t\t connect time\t\ttransfer time\tspeed(bytes/sec)\n");
int i;
for(i=0;i<14;i++)
printf("%s\t\t\t%.3f\t\t%.3f\t\t\t%.3f\n",serv[i].servaddr,serv[i].con_time,serv[i].tra_time,1400.0/(serv[i].tra_time+serv[i].con_time));

}

void * calculate(void * arg)

{

int id=*((int*)arg);
char buf[100];
int sfd,n,sum;
time_t x,y,z;
struct sockaddr_in address;
while(1)
{
sfd=socket(AF_INET,SOCK_STREAM,0);
if(sfd==-1)
{printf("socket error\n");exit(1);}
bzero(&address,sizeof(address));
address.sin_family=AF_INET;
address.sin_port=htons(3128);
inet_pton(AF_INET,serv[id].servaddr,&address.sin_addr);
time(&x);
printf("%d...sent request....\n",id);
connect(sfd,(struct sockaddr *)&address,sizeof(address));
time(&y);
write(sfd,url,strlen(url));
sum=0;
while((n=read(sfd,buf,100))>0) sum+=n;
time(&z);

serv[id].con_time=difftime(y,x);
serv[id].tra_time=difftime(z,y);
display();
close(sfd);
sleep(2);



}
}



int main()
{
pthread_t g[14];
	strcpy(serv[0].servaddr,"172.30.0.7");
	strcpy(serv[1].servaddr,"172.30.0.8");
	strcpy(serv[2].servaddr,"172.30.0.9");
	strcpy(serv[3].servaddr,"172.30.0.10");
	strcpy(serv[4].servaddr,"172.30.0.11");
	strcpy(serv[5].servaddr,"172.30.0.12");
strcpy(serv[6].servaddr,"172.30.0.13");
strcpy(serv[7].servaddr,"172.30.0.14");
strcpy(serv[8].servaddr,"172.30.0.15");
strcpy(serv[9].servaddr,"172.30.0.16");
strcpy(serv[10].servaddr,"172.30.0.17");
strcpy(serv[11].servaddr,"172.30.0.18");
strcpy(serv[12].servaddr,"172.30.0.19");
strcpy(serv[13].servaddr,"172.30.0.20");
	//opf=open("byt", O_WRONLY);
	int j;int i;
	for(i=0; i<14; i++)
	{	j=i;pthread_create(&g[i], NULL, &calculate, (void*)&j);}
for(i=0; i<14; i++)

	pthread_join(g[i], NULL);

exit(0);
}
