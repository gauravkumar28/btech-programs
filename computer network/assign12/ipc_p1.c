#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/ip.h>
#include<errno.h>
#include<string.h>
#include<pthread.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<netinet/udp.h>

int sfd;
unsigned short csum (unsigned short *buf, int nwords)
{
	unsigned long sum;
	for (sum = 0; nwords > 0; nwords--)
		sum += *buf++;
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	return ~sum;
}

void *send_msg(void* arg)
{

        printf("send\n");
	char buf[4096],msg[512];
	struct ip* iph=(struct ip*)buf;
iph->ip_hl=5;
iph->ip_v=4;
iph->ip_tos=0;
iph->ip_len=20+sizeof(struct ip);
iph->ip_id=0;
	iph->ip_off=0;
	iph->ip_ttl=64;
	iph->ip_p=21;
	inet_pton(AF_INET,"127.0.0.1",&(iph->ip_src));
	inet_pton(AF_INET,"127.0.0.1",&(iph->ip_dst));
	iph->ip_sum=csum((unsigned short*)buf,iph->ip_len>>1);
int one =1;
	const int *val=&one;
	if(setsockopt(sfd,IPPROTO_IP,IP_HDRINCL,val,sizeof(one))<0)
	{
		printf("hdr include error\n");
	}



struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_port=htons(3500);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
	while(1)
	{
		fgets(msg,512,stdin);
		strcpy(buf+5*4,msg);
		if(sendto(sfd,buf,iph->ip_len,0,(struct sockaddr*) &server,sizeof server)<0)
			perror("Send error\n");
	}





}
void *recv_msg(void* arg)
{
printf("receive\n");
	char buf[4096];
	struct ip* ipheader=(struct ip*)buf;
	struct sockaddr_in client;
	int length;
	while(1)
	{
		if(recvfrom(sfd,buf,4096,0,(struct sockaddr*) &client,&length)<0)
			perror("receive error\n");


		printf("version is:%d\n",ipheader->ip_v);
		printf("header length:%d\n",ipheader->ip_hl*4);
		printf("service:%d\n",ipheader->ip_tos);
		printf("len:%d\n",ipheader->ip_len);
		printf("sequence id:%d\n",ipheader->ip_id);
		printf("frag offset:%d\n",ipheader->ip_off);
		printf("ttl:%d\n",ipheader->ip_ttl);
		printf("Higher level protocol:%u\n",ipheader->ip_p);
		printf("Check Sum:%d\n",ipheader->ip_sum);
		printf("Source addr:%s\n",inet_ntoa(ipheader->ip_src));
		printf("Destination addr:%s\n\n\n",inet_ntoa(ipheader->ip_dst));

		printf("msg received is:%s\n",buf+sizeof(struct ip));
	}

}

int main()
{


sfd=socket(AF_INET,SOCK_RAW,20);
if(sfd==-1)
{

perror("socket...");exit(1);
}
pthread_t t1,t2;
pthread_create(&t1,NULL,send_msg,NULL);
pthread_create(&t2,NULL,recv_msg,NULL);
pthread_join(t1,NULL);
pthread_join(t2,NULL);

return 0;
}
