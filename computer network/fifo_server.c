#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>
#include<string.h>

char serverbuf[1000];
char clintbuf[1000];
int main()
{
int a,fds,fdc,n;
if((a=mkfifo("/home/gaurav/cn/servertext.txt",0666))<0)
printf("\n fifo error");
if((a=mkfifo("/home/gaurav/cn/clinttext.txt",0666))<0)
printf("\n fifo error");
fds=open("/home/gaurav/cn/servertext.txt",O_RDWR);
fdc=open("/home/gaurav/cn/clinttext.txt",O_RDWR);
printf("\n welcome to  server process");
while(1)
{

printf("\n server::\t");
gets(clintbuf);
write(fdc,clintbuf,strlen(clintbuf));

printf("\n clint::\t");
n=read(fds,serverbuf,1000);
write(1,serverbuf,n);
}
close(fds);
close(fdc);

return 0;
}
