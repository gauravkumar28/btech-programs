/*
Project group: NITW-SUMMER-PROJECT-2013-HPC-FTE


 AIM: Enabling huge page size under Linux environment
   Users can use the huge page support in Linux kernel by either using the mmap
   system call or standard SYSV shared memory system calls (shmget, shmat).
   This is only demo program to change the page sige and perform huge operation
   we have to fallow few commands before we run the program in linux environment
   We know that we can allocate upto 2MB page size so if we want memory to occupy 6Mb page size we need three huge page
   # cat /proc/meminfo | grep Hugepagesize Hugepagesize : 2048kB  //to chnage page size
   #echo 5> /proc/sys/vm/nr_hugepages   // to set no of pages
   # cat /proc/meminfo | grep Huge  //to seet huge page status  and setting




INPUT: HUGE inpute order of MB or GB
OUTPUT: program is able to allocate huge memory  for that size


Application: this is very useful for handling big data used in mining and social media. using shared memory we can implement whole database on memory. oracle is using this concept for dbms systems

Improvement: It is just a demo program to show that huge page enabling concept is working. we have not implemented so for for any application. I am geting few problem in accessing data.


*/
 
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<errno.h>
int length;
void write_byte(void *map_addr)
{
int i;
int *buf=(int*)map_addr;
for(i=0;i<length/4;i++)
*(buf+i)=2;
}
void read_byte(int fd)
{
int a,i;
for(i=0;i<length/4;i++)
{read(fd,&a,4);
//printf("%d ",*((int*)map_addr+i));
printf("%d ",a);
}




}


int main(int argc,char *argv[])
{
printf("\n enter the memory size : size should be multiple of 2*1024*1024 ");

length=atoi(argv[1]);

int fd=open("project1",O_RDWR|O_CREAT);
if(fd==-1)
{
perror("File Not Opened");
exit(1);
}



void * map_addr;
map_addr=mmap(NULL,length,PROT_READ|PROT_WRITE,MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB,fd,0);
if(map_addr==MAP_FAILED)
{
perror("MAP Error");
exit(1);
}
printf("\n Address Is %p\n",map_addr);
write_byte(map_addr);

system("cat /proc/meminfo | grep Huge");
//read_byte(fd);
munmap(map_addr,length);
close(fd);

unlink("project1");

return 0;
}
