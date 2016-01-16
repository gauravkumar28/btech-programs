#include<stdio.h>
#include<sys/socket.h>
#include<netinet/ip.h>
#include<netinet/tcp.h>
#include<unistd.h>
#include<stdlib.h>

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



void *sender(void * arg)
{

char buf[4096];
struct ip* ip_hdr=buf;
char buff[512];

ip_hdr->ip_hl=5;
ip_hdr->ip_v=4;
ip_hdr->ip_tos=0;
ip_hdr->ip_len=20+sizeof buff;
ip_hdr->ip_id=0;
ip_hdr->ip_off=0;
ip_hdr->ip_ttl=64;
ip_hdr->ip_p=199;
inet_pton(AF_INET,"127.0.0.1",&(ip_hdr->ip_src));
inet_pton(AF_INET,"127.0.0.1",&(ip_hdr->ip_dst));
ip_hdr->ip_sum=csum((unsigned short*)buf,9);



 int one = 1;
    const int *val = &one;
    if (setsockopt (sfd, IPPROTO_IP, IP_HDRINCL, val, sizeof (one)) < 0)
      printf ("Cannot set HDRINCL!\n");
struct sockaddr_in addr;
addr.sin_family=AF_INET;
addr.sin_port=htons(3500);
inet_pton(AF_INET,"127.0.0.1",&addr.sin_addr);


while(1)
{
fgets(buff,512,stdin);
memcpy(buf+5*4,buff,512);

sendto(sfd,buf,ip_hdr->ip_len,0,(struct sockaddr *) &addr,sizeof(addr));
}






}


void *reciever(void *arg)
{
char buf[4096];
while(1)
{
recvfrom(sfd,buf,4096,0,NULL,NULL);
printf("%s",buf+sizeof(struct ip));
memset(buf,0,4096);
}

}


int main()
{

sfd=socket(AF_INET,SOCK_RAW,100);
if(sfd==-1)
{
perror("socket");exit(1);}

pthread_t p,q;
pthread_create(&p,NULL,sender,NULL);
pthread_create(&q,NULL,reciever,NULL);
pthread_join(p,NULL);
return 0;

}


