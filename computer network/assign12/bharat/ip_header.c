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
int main()
{
	char buf[4096];
	int length;
	int sfd=socket(AF_INET,SOCK_RAW,IPPROTO_TCP);
	struct ip* iph=(struct ip*)buf;
	struct tcphdr* tcph=(struct tcphdr*)(buf+sizeof (struct ip));
;
	struct sockaddr_in client;
	recvfrom(sfd,buf,4096,0,(struct sockaddr*)&client,&length);
	printf("---IP HEADER INFO IS ---\n");
	printf("version is%d\n",iph->ip_v);
	printf("header length is %d\n",iph->ip_hl*4);
	printf("type of service is %d\n",iph->ip_tos);
	printf("length is %d\n",iph->ip_len);
	printf("packet id no %d\n",iph->ip_id);
	printf("offset value %d\n",iph->ip_off);
	printf("ttl is %d\n",iph->ip_ttl);
	printf("higher layer protocol is %u\n",iph->ip_p);
	printf("check sum is%x\n",iph->ip_sum);
	printf("source ip addr %s\n",inet_ntoa(iph->ip_src));
	printf("dest ip addr %s\n",inet_ntoa(iph->ip_dst));
	printf("\n\n");

	/*printf("---tcp header is---\n");
	printf("tcp source port no is %d\n",tcph->source);
	printf("tcp dest port no is %d\n",tcph->th_dport);
	printf("sequence is%d\n",tcph->th_seq);
	printf("acknowledgement is %s\n",tcph->th_ack);
	printf("x2 is %s\n",tcph->th_x2);
	printf("offset is %s\n",tcph->th_off);
	printf("Syn flag is%s\n",tcph->th_flags);
	printf("window size is %s\n",tcph->th_win);
	printf("tcp sum is %d\n",tcph->th_sum);
	printf("urp is %s\n",tcph->th_urp);*/
	struct udphdr* ud=(struct udphdr*)(buf+20);
	printf("udp source port:%d\n",htons(ud->source));
	printf("udp destination port:%d\n",htons(ud->dest));
	printf("udp len:%d\n",ud->len);
	printf("udp check:%x\n",ud->check);

	return 0;
}
