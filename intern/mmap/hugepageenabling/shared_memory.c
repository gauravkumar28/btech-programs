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
OUTPUT: program is able to allocate huge shared  memory  for that size  which can we used for many application like database and data mining


Application: this is very useful for handling big data used in mining and social media. using shared memory we can implement whole database on memory. oracle is using this concept for dbms systems


*/


#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

#define MB_1 (1024*1024)

char  *a;
int shmid1,length;

void init_hugetlb_seg()
{
  shmid1 = shmget(2, length, SHM_HUGETLB| IPC_CREAT | SHM_R| SHM_W);
  if ( shmid1 < 0 ) {
    perror("shmget   --");
    exit(1);
  }
  printf(" shmid: 0x%x\n", shmid1);
  a = shmat(shmid1, 0, 0);
  if (a == (char *)-1) {
    perror("Shared memory attach failure");
    shmctl(shmid1, IPC_RMID, NULL);
    exit(2);
  }
}

void wr_to_array()
{
  int i;
  for( i=0 ; i<length ; i++) {
    a[i] = 'A';
  }
}

void rd_from_array()
{
  int i, count = 0;
  for( i=0 ; i<length ; i++)
    if (a[i] == 'A') count++;
  if (count==i)
    printf("HugeTLB read success \n");
  else
    printf("HugeTLB read failed \n");
}

int main(int argc, char *argv[])
{
if(argc==1)
length=4*1024*1024;
else
length=atoi(argv[1]);

  init_hugetlb_seg();
  printf("HugeTLB memory segment initialized !\n");
  printf("Press any key to write to memory area\n");
  getchar();
  wr_to_array();
  printf("Press any key to rd from memory area\n");
  getchar();
  rd_from_array();
  shmctl(shmid1, IPC_RMID, NULL);
  return 0;
}
