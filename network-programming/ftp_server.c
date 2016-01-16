#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<time.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
void doftp(int x);
int main()
{
int sfd,nsfd,pid,length;
struct sockaddr_in my_addr,client_addr;
if((sfd=socket(AF_INET,SOCK_STREAM,0))<0)
{printf("Server: Socket Error:%d\n",errno);exit(0);}
bzero((char *)&my_addr,sizeof(my_addr));
my_addr.sin_family=AF_INET;
my_addr.sin_port=htons(5500);
my_addr.sin_addr.s_addr=htons(INADDR_ANY);
if(bind(sfd,(struct sockaddr *)&my_addr,sizeof(my_addr))<0)
{
printf("Server: Bind Error:%d\n",errno);exit(0);}
listen(sfd,5);
while(1)
{
length=sizeof(client_addr);
if((nsfd=accept(sfd,(struct sockaddr *)&client_addr,&length))<0)
{
printf("Server : accept  error : %d\n",errno);exit(0);}
if(fork()==0)
{
close(sfd);
doftp(nsfd);
close(nsfd);
exit(0);
}
else
close(nsfd);
}
}

void doftp(int nsfd)
{

char  fname[256],p[256];


recv(nsfd,fname,256,0);
printf("%s\n",fname);
FILE *fp;
/*int j;
for(j=0;j<strlen(fname)&&fname[j]!='\0';j++)
p[j]=fname[j];
p[j]='\0';
printf("%s\n",p);*/
if((fp=fopen("text.txt","r"))==NULL)
{
printf("\n file open error: %d\n",errno);
exit(0);

}
int c;


int fsize=0;
while((c=getc(fp))!=EOF){

fsize++;}
fclose(fp);
printf("%d\n",fsize);


int num_block=fsize/4096;
int last_block=fsize%4096;
int i;
char msg[4096];
printf("%d\t%d\n",num_block,last_block);
if((fp=fopen("text.txt","r"))==NULL)
{
printf("\n file open error: %d\n",errno);
exit(0);

}
for(i=0;i<num_block;i++)
{
int nread=fread(msg,sizeof(char),4096,fp);
printf("%s\n",msg);
send(nsfd,msg,4096,0);


}
memset(msg,0,4096);
printf("%s",msg);
int nread=fread(msg,sizeof(char),last_block,fp);
if(nread==0)
{
printf("no read");

}
printf("%s",msg);
send(nsfd,msg,last_block,0);
fclose(fp);
return;
}


