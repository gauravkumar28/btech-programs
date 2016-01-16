#include<stdio.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
    int sd,con,port,i,Res;
    char content[30];
    struct sockaddr_in cli;

    if((sd=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP))==-1)
    {
        printf("\nSocket problem");
        return 0;
    }

    bzero((char*)&cli,sizeof(cli));
    cli.sin_family = AF_INET;
    printf("ENTER PORT NO:\n");
    scanf("%d",&port);
    cli.sin_port=htons(port);
    cli.sin_addr.s_addr=htonl(INADDR_ANY);

    con=connect(sd,(struct sockaddr*)&cli,sizeof(cli));

    if(con==-1)
    {
        printf("\nConnection error");
        return 0;
    }

    int m,n; 
	printf("enter no.: ");
    memset(content,0,30);
	scanf("%d",&m);
    sprintf(content,"%d",m);
    send(sd,content,30,0);
	
	printf("output: ");
    memset(content,0,30);
	recv(sd,content,30,0);
	printf("%s\n",content);
    return 0;
}
