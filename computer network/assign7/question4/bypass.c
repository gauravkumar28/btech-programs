#include<sys/socket.h>
#include<sys/types.h>
#include<netdb.h>
#include<netinet/in.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>


int main()
{
char port1[10],port2[10];
char buf[100];
char record[5][30];
int sfd,nsfd,size1;
int asfd;
strcpy(record[0],"1600");
strcpy(record[1],"1700");
strcpy(record[2],"1800");
strcpy(record[3],"1900");
strcpy(record[4],"2000");

struct sockaddr_in bypass1,bypass2,group1,group2;
sfd=socket(AF_INET,SOCK_STREAM,0);
if(sfd==-1)
{
printf("socket error\n");exit(1);}

bzero((char*)&bypass1,sizeof(bypass1));
bypass1.sin_family=AF_INET;
bypass1.sin_addr.s_addr=INADDR_ANY;
bypass1.sin_port=htons(2500);

bind(sfd,(struct sockaddr *)&bypass1,sizeof(bypass1));
listen(sfd,5);
size1=sizeof(group1);
while(1)
{
nsfd=accept(sfd,(struct sockaddr*)&group1,&size1);

if(nsfd==-1)
{printf("error");exit(1);}
memset(buf,0,100);
recv(nsfd,buf,100,0);
printf("client said%s\n",buf);
int j;

for(j=0;buf[j]!=' ';j++)
port1[j]=buf[j];
port1[j+1]='\0';
j++;
int k=0;
for(j;j<strlen(buf);j++)
port2[k++]=buf[j];

//printf("%s   \t  %s",port1,port2);
memset(buf,0,100);
int i;
for(i=0;i<5;i++)
if(strcmp(port2,record[i])==0)
{printf("port found\n");break;}
if(i==5)
{printf("wrong request for port\n");}
else{
asfd=socket(AF_INET,SOCK_STREAM,0);
if(asfd==-1)
{printf("socket error\n");exit(1);}
bzero(&bypass2,sizeof(bypass2));
bypass2.sin_family=AF_INET;
bypass2.sin_addr.s_addr=inet_addr("127.0.0.1");
bypass2.sin_port=htons(atoi(port2));
if(connect(asfd,(struct sockaddr*)&bypass2,sizeof(bypass2))==-1)
{perror("error");exit(1);}
memset(buf,0,100);

strcpy(buf,port1);

send(asfd,buf,100,0);
}}
return 0;
}
