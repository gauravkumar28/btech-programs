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
unsigned short csum (unsigned short *buf, int nwords)
{
	unsigned long sum;
	for (sum = 0; nwords > 0; nwords--)
		sum += *buf++;
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	return ~sum;
}
int sfd;
int id[100],count=0;

int main()
{
sfd=socket(AF_INET,SOCK_RAW,100);
if(sfd==-1)
{

perror("socket...");exit(1);
}


while(1)
{

char buf[4096];
struct ip* ipheader=(struct ip*)buf;
struct sockaddr_in client;
int length,cid;

if(recvfrom(sfd,buf,4096,0,(struct sockaddr*) &client,&length)>0)
//{perror("receive error\n");exit(0);}
{struct ip* ipheader=(struct ip*)buf;
printf("Higher level protocol:%u\n",ipheader->ip_p);
printf("msg received is:%s\n",buf+sizeof(struct ip));
char * a=buf+sizeof(struct ip);
cid=a[0]-48;
printf("%d\n",cid);
}
char msg[4096];
strcpy(msg,buf+sizeof(struct ip)+1);
int i;
for(i=0;i<count;i++)
{if(id[i]==cid)
break;
}
if(i==count)
id[count++]=cid;

for(i=0;i<count;i++)
{

if(id[i]!=cid)
{printf("%d\n",id[i]);
char buf[4000];
struct ip* iph=(struct ip*)buf;
iph->ip_hl=5;
iph->ip_v=4;
iph->ip_tos=0;
iph->ip_len=20+sizeof(struct ip);
iph->ip_id=0;
	iph->ip_off=0;
	iph->ip_ttl=64;
	iph->ip_p=id[i];
	inet_pton(AF_INET,"127.0.0.1",&(iph->ip_src));
	inet_pton(AF_INET,"127.0.0.1",&(iph->ip_dst));
	iph->ip_sum=csum((unsigned short*)buf,iph->ip_len>>1);
int one =1;
	const int *val=&one;
	if(setsockopt(sfd,IPPROTO_IP,IP_HDRINCL,val,sizeof(one))<0)
	{
		printf("hdr include error\n");
	}

printf("%d\n",iph->ip_p);

struct sockaddr_in server;
	server.sin_family=AF_INET;
	server.sin_port=htons(2500);
	server.sin_addr.s_addr=inet_addr("127.0.0.1");
strcpy(buf+5*4,msg);
printf("%s\n",buf+20);
		if(sendto(sfd,buf,iph->ip_len,0,(struct sockaddr*) &server,sizeof server)<0)
			perror("Send error\n");
}
}
}
return 0;
}
