#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/select.h>
#include<sys/un.h>
#include<netinet/ip.h>
#include<netinet/udp.h>
unsigned short csum (unsigned short *buf, int nwords)
{
	unsigned long sum;
	for (sum = 0; nwords > 0; nwords--)
		sum += *buf++;
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	return ~sum;
}


int main()
{
	int rsfd=socket(AF_INET,SOCK_RAW,IPPROTO_UDP);
	char buf[4096]={0};
	char msg[1000]={0};
	struct ip* ipheader=(struct ip*)buf;
	ipheader->ip_hl=5;
	ipheader->ip_v=4;
	ipheader->ip_tos=0;
	ipheader->ip_len=20+8+sizeof(msg);
	ipheader->ip_id=0;
	ipheader->ip_off=0;
	ipheader->ip_ttl=64;
	ipheader->ip_p=17;
	inet_pton(AF_INET,"127.0.0.1",&(ipheader->ip_src));
	inet_pton(AF_INET,"127.0.0.1",&(ipheader->ip_dst));
	ipheader->ip_sum=csum((unsigned short*)buf,9);

    	int k=1;
    	const int *l = &k;
    	if (setsockopt (rsfd, IPPROTO_IP, IP_HDRINCL ,l, sizeof (k)) < 0)
     		 printf ("ERROR IN HDRINCL!\n");
      
	struct udphdr *udpheader=(struct udphdr*)(buf+ipheader->ip_hl*4);

	udpheader->source=htons(3400);
	udpheader->dest=htons(2300);
	udpheader->len=htons(8+sizeof(msg));
	udpheader->check=0;
	memcpy(buf+20,udpheader,8);

	struct sockaddr_in addr;
	addr.sin_port=htons(2300);
	addr.sin_family=AF_INET;
	inet_pton(AF_INET,"127.0.0.1",&(addr.sin_addr));
	while(1)
	{
		fgets(msg,1000,stdin);
		strcpy(buf+28,msg);
		sendto(rsfd,buf,4096,0,(struct sockaddr*) &addr,sizeof addr);
	}

	return 0;
}
