#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<string.h>
#include<assert.h>
#include<errno.h>


int main()
{
int a,i;
int fd=open("demo.txt",O_RDWR|O_CREAT);
int *map_addr=mmap(0,2*1024*1024,PROT_WRITE,MAP_PRIVATE |MAP_HUGETLB |MAP_ANONYMOUS,fd,0);
for(i=0;i<512*1024;i++)
*(map_addr+i)=2;

for(i=0;i<512*1024;i++)
{
read(fd,&a,4);
printf("%d ",a);


}
munmap(map_addr,2*1024*1024);
close(fd);
return 0;
}

