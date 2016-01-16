

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>           
#include <string.h>           

#include <netdb.h>          
#include <sys/types.h>        
#include <sys/socket.h>       
#include <netinet/in.h>       
#include <netinet/ip.h>       
#include <arpa/inet.h>        
#include <sys/ioctl.h>        
#include <bits/ioctls.h>      
#include <net/if.h>           
#include <linux/if_ether.h>   
#include <linux/if_packet.h>  
#include <net/ethernet.h>

#include <errno.h>           

//struct for ARP header
typedef struct _arp_hdr arp_hdr;
struct _arp_hdr {
  unsigned short htype;
  unsigned short ptype;
  unsigned char hlen;
  unsigned char plen;
  unsigned short opcode;
  unsigned char sender_mac[6];
  unsigned char sender_ip[4];
  unsigned char target_mac[6];
  unsigned char target_ip[4];
};

int main ()
{
  int i, status, frame_length, sd, bytes;
  char *interface, *target, *src_ip;
  arp_hdr arphdr;
  unsigned char *src_mac, *dst_mac, *ether_frame;
  struct addrinfo hints, *res;
  struct sockaddr_in *ipv4;
  struct sockaddr_ll device;
  struct ifreq ifr;
  void *tmp;

  tmp = (unsigned char *) malloc (6 * sizeof (unsigned char));
  if (tmp != NULL) {
    src_mac = tmp;
  } else {
    fprintf (stderr, "ERROR: Cannot allocate memory for array 'src_mac'.\n");
    exit (EXIT_FAILURE);
  }
  memset (src_mac, 0, 6 * sizeof (unsigned char));

  tmp = (unsigned char *) malloc (6 * sizeof (unsigned char));
  if (tmp != NULL) {
    dst_mac = tmp;
  } else {
    fprintf (stderr, "ERROR: Cannot allocate memory for array 'dst_mac'.\n");
    exit (EXIT_FAILURE);
  }
  memset (dst_mac, 0, 6 * sizeof (unsigned char));

  tmp = (unsigned char *) malloc (IP_MAXPACKET * sizeof (unsigned char));
  if (tmp != NULL) {
    ether_frame = tmp;
  } else {
    fprintf (stderr, "ERROR: Cannot allocate memory for array 'ether_frame'.\n");
    exit (EXIT_FAILURE);
  }
  memset (ether_frame, 0, IP_MAXPACKET * sizeof (unsigned char));

  tmp = (char *) malloc (40 * sizeof (char));
  if (tmp != NULL) {
    interface = tmp;
  } else {
    fprintf (stderr, "ERROR: Cannot allocate memory for array 'interface'.\n");
    exit (EXIT_FAILURE);
  }
  memset (interface, 0, 40 * sizeof (char));

  tmp = (char *) malloc (40 * sizeof (char));
  if (tmp != NULL) {
    target = tmp;
  } else {
    fprintf (stderr, "ERROR: Cannot allocate memory for array 'target'.\n");
    exit (EXIT_FAILURE);
  }
  memset (target, 0, 40 * sizeof (char));

  tmp = (char *) malloc (16 * sizeof (char));
  if (tmp != NULL) {
    src_ip = tmp;
  } else {
    fprintf (stderr, "ERROR: Cannot allocate memory for array 'src_ip'.\n");
    exit (EXIT_FAILURE);
  }
  memset (src_ip, 0, 16 * sizeof (char));
  strcpy (interface, "wlan0");
  if ((sd = socket (AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0) {
    perror ("socket() failed to get socket descriptor for using ioctl() ");
    exit (EXIT_FAILURE);
  }
  memset (&ifr, 0, sizeof (ifr));
  snprintf (ifr.ifr_name, sizeof (ifr.ifr_name), "%s", interface);
	ether_frame[6]=src_mac[0] = 0x00;
	ether_frame[7]=src_mac[1] = 0x0c;
	ether_frame[8]=src_mac[2] = 0x29;
	ether_frame[9]=src_mac[3] = 0x95;
	ether_frame[10]=src_mac[4] = 0x5e;
	ether_frame[11]=src_mac[5] = 0x56;
  printf ("MAC address for interface %s is ", interface);
  for (i=0; i<5; i++) {
    printf ("%02x:", src_mac[i]);
  }
  printf ("%02x\n", src_mac[5]);
  if ((device.sll_ifindex = if_nametoindex (interface)) == 0) {
    perror ("if_nametoindex() failed to obtain interface index ");
    exit (EXIT_FAILURE);
  }
  printf ("Index for interface %s is %i\n", interface, device.sll_ifindex);

  memset (dst_mac, 0xff, 6);
  strcpy (src_ip, "192.168.226.128");

  strcpy (target, "192.168.226.128");

  memset (&hints, 0, sizeof (struct addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = hints.ai_flags | AI_CANONNAME;
  if ((status = getaddrinfo (src_ip, NULL, &hints, &res)) != 0) {
    fprintf (stderr, "getaddrinfo() failed: %s\n", gai_strerror (status));
    exit (EXIT_FAILURE);
  }
  ipv4 = (struct sockaddr_in *) res->ai_addr;
  memcpy (&arphdr.sender_ip, &ipv4->sin_addr, 4);
  freeaddrinfo (res);
  if ((status = getaddrinfo (target, NULL, &hints, &res)) != 0) {
    fprintf (stderr, "getaddrinfo() failed: %s\n", gai_strerror (status));
    exit (EXIT_FAILURE);
  }
  ipv4 = (struct sockaddr_in *) res->ai_addr;
  memcpy (&arphdr.target_ip, &ipv4->sin_addr, 4);
  freeaddrinfo (res);
  device.sll_family = AF_INET;
  memcpy (device.sll_addr, src_mac, 6);
  device.sll_halen = htons (6);
  arphdr.htype = htons (1);

  arphdr.ptype = htons (ETH_P_IP);


  arphdr.hlen = 6;
  arphdr.plen = 4;
  arphdr.opcode = htons (1);
  memcpy (&arphdr.sender_mac, src_mac, 6);

  memset (&arphdr.target_mac, 0, 6);
  frame_length = 6 + 6 + 2 + 28;
  memcpy (ether_frame, dst_mac, 6);
  ether_frame[12] = ETH_P_ARP / 256;
  ether_frame[13] = ETH_P_ARP % 256;
  memcpy (ether_frame + 14, &arphdr, 28);

  if ((sd = socket (AF_INET, SOCK_RAW, htons (ETH_P_ALL))) < 0) {
    perror ("socket() failed ");
    exit (EXIT_FAILURE);
  }

  if ((bytes = sendto (sd, ether_frame, frame_length, 0, (struct sockaddr *) &device, sizeof (device))) <= 0) {printf("errno=%d\n",errno);
    perror ("sendto() failed");
    exit (EXIT_FAILURE);
  }
printf("dest mac=\t%02x:",dst_mac[0]);
printf("%02x:",dst_mac[1]);
printf("%02x:",dst_mac[2]);
printf("%02x:",dst_mac[3]);
printf("%02x:",dst_mac[4]);
printf("%02x:",dst_mac[5]);

  close (sd);
  free (src_mac);
  free (dst_mac);
  free (ether_frame);
  free (interface);
  free (target);
  free (src_ip);

  return (EXIT_SUCCESS);
}

