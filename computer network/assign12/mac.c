#include<sys/socket.h>
#include<sys/types.h>
#include<fcntl.h>
#include<errno.h>
#include<string.h>
#include<net/if_arp.h>
#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <err.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>

#include <net/if.h>
#include <netinet/ether.h>
int main(int argc,char **argv)
{
int sockfd;
struct ifi_info *ifi;
unsigned char *ptr;
struct arpreq arpreq;
struct sockaddr_in *sin;
sockfd=socket(AF_INET,SOCK_DGRAM,0);
for(ifi=get_ifi_info(AF_INET,0);ifi!=NULL;ifi=ifi->ifi_next)
{
printf("%s: ",sock_ntop(ifi->ifi_addr,sizeof(struct sockaddr_in*)));
sin=(struct sockaddr_in *)&arpreq.arp_pa;
memcpy(sin,ifi->ifi_addr,sizeof(struct sockaddr_in*));
if(ioctl(sockfd,SIOCGARP,&arpreq)<0)
{
perror("ioctl SIOCGARP");
continue;
}
ptr=&arpreq.arp_ha.sa_data[0];
printf("%x:%x:%x:%x:%x:%x\n",*ptr,*(ptr+1),*(ptr+2),*(ptr+3),*(ptr+4),*(ptr+5));
}

return 0;
}

