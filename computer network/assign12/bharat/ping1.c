#include "headers.c"
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


void signalhandler()
{

printf("\n---%s ping statistics ---\n",pingaddr);
printf("%d packets transmitted, %d received, %f percentage packet loss,time %f ms\n",noofpackets,success,(double)(noofpackets-fail)/(double)(noofpackets)*100,totaltime); 
printf("rtt min/avg/max %f/%f/%f ms\n",mintime,totaltime/((double)noofpackets),maxtime);
exit(0);
}



int main(int argc,int *argv[])
{
	if(argc!=2)
	{printf("error invalid arguments\n");
	exit(1);}
        signal(SIGINT,signalhandler);

int rsfd=socket(AF_INET,SOCK_RAW,IPPROTO_ICMP);
if(rsfd<0)
{
perror("socket error\n");
exit(1);
}

char buf[1000]={0};
char msg[1000]={0};
struct ip* ipheader=(struct ip*)buf;
ipheader->ip_hl=5;
ipheader->ip_v=4;
ipheader->ip_tos=0;
ipheader->ip_len=20+8;//8 for icmp header
ipheader->ip_id=0;
ipheader->ip_off=0;
ipheader->ip_ttl=64;
ipheader->ip_p=1;//protocol 1 for icmp
inet_pton(AF_INET,"127.0.0.1",&(ipheader->ip_src));
inet_pton(AF_INET,argv[1],&(ipheader->ip_dst));
strcpy(pingaddr,argv[1]);
ipheader->ip_sum=csum((unsigned short*)buf,9);
    int k=1;
    const int *l = &k;
    if (setsockopt (rsfd, IPPROTO_IP, IP_HDRINCL, l, sizeof (k)) < 0)
      perror ("HDRINCL ERROR\n");


struct icmphdr  *ichdr=(struct icmphdr*)(buf+20);
ichdr->type=8;
ichdr->code=0;
ichdr->checksum=csum((unsigned short*) (buf+20),1);

struct sockaddr_in addr,client;
addr.sin_family=AF_INET;
inet_pton(AF_INET,argv[1],&(addr.sin_addr));
struct timeval tvstart,tvend,timeout;
socklen_t len=sizeof addr;
timeout.tv_sec = 1;
timeout.tv_usec = 0;
      if (setsockopt (rsfd,SOL_SOCKET,SO_RCVTIMEO,(void*)&timeout,sizeof(timeout)) < 0)//setting timeout for recv
        perror("error in sockopt\n");
printf("PING %s (%s) 56(84) bytes of data.\n",argv[1],argv[1]);

while(1)
{
gettimeofday(&tvstart,NULL);
if(sendto(rsfd,buf,28,0,SA &addr,sizeof addr)<0)//sending only header with no msg
perror("Send error\n");
noofpackets++;
int r;
r=recvfrom(rsfd,msg,1000,0,SA &client,&len);
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
/*struct ip *i;
i=(struct ip*)msg;*/
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

