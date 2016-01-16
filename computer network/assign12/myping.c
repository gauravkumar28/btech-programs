#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<netinet/ip.h>
#include<netinet/ip_icmp.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<signal.h>

unsigned short csum(unsigned short *buf,int nowords)
{
	unsigned short sum=0;
    for ( ; nowords > 0; nowords--)
    {sum += *buf;buf++;}
    return ~sum;
}

char pingaddr[100]={0};
double maxtime=-1,mintime=10000,totaltime=0;

int noofpackets=0,success=0,fail=0;


void ping()
{

printf("\n---%s ping statistics ---\n",pingaddr);
printf("%d packets transmitted, %d received, %f percentage packet loss,time %f ms\n",noofpackets,success,(double)(noofpackets-fail)/(double)(noofpackets)*100,totaltime); 
printf("rtt min/avg/max %f/%f/%f ms\n",mintime,totaltime/((double)noofpackets),maxtime);
exit(0);
}

int main(int argc,char* argv[])
{
if(argc<2)
{

printf("argument error\n");exit(1);}

signal(SIGINT,ping);

int rsfd=socket(AF_INET,SOCK_RAW,IPPROTO_ICMP);
if(rsfd==-1)
{perror("socket");exit(1);}
char buf[1000]={0};
char msg[1000]={0};
struct ip* ipheader=(struct ip*)buf;
ipheader->ip_hl=5;
ipheader->ip_v=4;
ipheader->ip_tos=0;
ipheader->ip_len=20+8;
ipheader->ip_id=0;
ipheader->ip_off=0;
ipheader->ip_ttl=64;
ipheader->ip_p=1;
inet_pton(AF_INET,"127.0.0.2",&(ipheader->ip_src));
inet_pton(AF_INET,argv[1],&(ipheader->ip_dst));
strcpy(pingaddr,argv[1]);
ipheader->ip_sum=csum((unsigned short *)buf,9);
int a=1;
int *one=&a;
if(setsockopt(rsfd,IPPROTO_IP,IP_HDRINCL,one,sizeof(a))<0)
{perror("HDRINCL ERROR\n");
exit(1);
}

struct icmphdr *ihdr=(struct icmphdr*)(buf+20);
ihdr->type=8;
ihdr->code=0;
ihdr->checksum=csum((unsigned short*)(buf+20),1);


struct sockaddr_in my,client;
my.sin_family=AF_INET;
inet_pton(AF_INET,argv[1],&(my.sin_addr));
struct timeval tvstart,tvend,timeout;
socklen_t len=sizeof(my);
timeout.tv_sec=1;
timeout.tv_usec=0;
if(setsockopt(rsfd,SOL_SOCKET,SO_RCVTIMEO,(void*)&timeout,sizeof(timeout)) < 0)
{

perror("sockopt error");exit(1);}
printf("PING %s (%s) 56(84) bytes of data.\n",argv[1],argv[1]);
while(1)
{
gettimeofday(&tvstart,NULL);
if(sendto(rsfd,buf,28,0,(struct sockaddr*)&my,sizeof(my))<0)
perror("send error");
noofpackets++;
int r;
r=recvfrom(rsfd,buf,1000,0,(struct sockaddr*)&client,&len);
gettimeofday(&tvend,NULL);
double timeelapsed=(double)(tvend.tv_sec-tvstart.tv_sec)*1000+((double)(tvend.tv_usec-tvstart.tv_usec))/1000;
totaltime+=timeelapsed;


if(r==-1)
{
fail++;
}
else
{
success++;

printf("64 bytes from %s: time=%f ms\n",argv[1],timeelapsed);
if(timeelapsed>maxtime)
maxtime=timeelapsed;
if(timeelapsed<mintime)
mintime=timeelapsed;
sleep(1);
}
}
return 0;
}
