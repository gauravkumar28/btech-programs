#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>
int main(int argc,char*argv[])
{int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    if (argc < 3) {
      printf("argument error");
       exit(0);
    }
    portno = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        {printf("error in socket");exit(0);}
    server = gethostbyname(argv[1]);
    if (server == NULL) {
       printf("wrong hostname");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
        {printf("connect error");exit(0);}

while(1)
{
    printf("Please enter the message: ");
    bzero(buffer,100);
    fgets(buffer,100,stdin);
send(sockfd,buffer,strlen(buffer),0);
bzero(buffer,100);
recv(sockfd,buffer,100,0);
printf("server said\t%s\n",buffer);

}

close(sockfd);
return 0;
}
