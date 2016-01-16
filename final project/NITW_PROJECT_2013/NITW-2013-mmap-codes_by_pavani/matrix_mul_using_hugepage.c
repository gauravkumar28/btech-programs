/*
Project group: NITW-SUMMER-PROJECT-2013-HPC-FTE
NAME: GAURAV KUMAR

 AIM: Enabling huge page size under Linux environment and perform matrix multiplication for huge data
   Users can use the huge page support in Linux kernel by either using the mmap
   system call or standard SYSV shared memory system calls (shmget, shmat).
   This is only demo program to change the page sige and perform huge operation
   we have to follow few commands before we run the program in linux environment
   We know that we can allocate upto 2MB page size so if we want memory to occupy 6Mb page size we need three huge page
   # cat /proc/meminfo | grep Hugepagesize Hugepagesize : 2048kB  //to chnage page size
   #echo 5> /proc/sys/vm/nr_hugepages   // to set no of pages
   # cat /proc/meminfo | grep Huge  //to seet huge page status  and setting




INPUT: matrix size and block_size
OUTPUT: output matrix C


Application: This is very useful for handling big data used in mining and social media. Using shared memory we can implement whole database on memory. Oracle uses this concept for dbms systems


performance :It is not verified  

*/

//header  files 
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

int block_size,nRows,nCols,padding;
int seek=0;

int *MatrixA,*MatrixB,*MatrixC;

//printing matrix...............

void printMatrix(char *name)
{
	FILE *fp=fopen(name,"r");
	if(fp==NULL)
	{
		perror("Error in Opening File");
		exit(1);
	}
	int i,j;
	int val,nread;
	for(i=0;i<nRows;i++)
	{
		for(j=0;j<nCols;j++)
		{

			nread=fread(&val,sizeof(int),1,fp);
			assert(nread==1);
			printf("%d ",val);

		}
		for(j=0;j<padding;j++)
		{

			nread=fread(&val,sizeof(int),1,fp);
			assert(nread==1);
			printf("%d ",val);

		}

		printf("\n");
	}

	fclose(fp);
}

// block by block matrix multiply............

int  block_by_block_multiply()
{
	size_t i,j,k;
	int sum;

	sum=0;
	for(j=0;j<block_size/4;j++)
	{
		sum+=MatrixA[j]*MatrixB[j];
	}
	return sum;


}




//mapping  block to memory



	


int* map_block(char * name,int mode,int rowindex,int colindex)
{
	int fd;
	if(mode==1)
		fd=open(name,O_RDONLY);
	else if(mode==2)
 		fd=open(name,O_RDWR);
	if(fd==-1)
	{

		perror("File not Opened  ");
		exit(1);
	}

	int cur_position =rowindex*nRows*4+colindex*block_size;
	lseek(fd,cur_position,SEEK_SET);

	int *map_addr=NULL;
	if(mode==1)
		map_addr=mmap(0,block_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	else if(mode==2)
		map_addr=mmap(0,block_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	if(map_addr==MAP_FAILED)
	{
		perror("MMAP Error");exit(1);
	}
	int i,a;
	int *buf=(int*)map_addr;
	if(mode!=2)
	for(i=0;i<block_size/4;i++)
	{
	
		*(buf++)=2;
	
	}

	close(fd);
	return map_addr;

}

/*

mapping matrix  chunk to memory  with different offset the previous fun
used for matrix A only



int* map_block2(char * name,int mode,int rowindex,int colindex)
{
int fd;
		if(mode==1)
				fd=open(name,O_RDONLY);
		else if(mode==2)
				 fd=open(name,O_RDWR);
		if(fd==-1)
			{

					perror("File not Opened  ");
					exit(1);
			}

int cur_position =rowindex*4+colindex*block_size;
lseek(fd,cur_position,SEEK_SET);
int *map_addr=NULL;
				if(mode==1)
					map_addr=mmap(0,block_size,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_HUGETLB |MAP_ANONYMOUS,fd,0);
				else if(mode==2)
					map_addr=mmap(0,blockk_size,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_HUGETLB |MAP_ANONYMOUS,fd,0);
				if(map_addr==MAP_FAILED)
					{
						perror("MMAP Error ");exit(1);
					}
int i,a;
int *buf=(int*)map_addr;
for(i=0;i<block_size/4;i++)
{

*(buf++)=2;

}
close(fd);
return map_addr;

}
*/

/* main function to map chunk by chunk and perform 
multiplication
multiplication is row by row
*/

void  map_Matrix()
{

	int i,j,k,index;
	int fd=open("./MatrixC",O_RDWR);
	if(fd==-1)
	{
		perror("File not opened ");
		exit(1);

	}

	for(i=0;i<(nRows);i++)
	{
		//printf(" %d \n ",i+1);
		for(j=0;j<(nCols);j++)
		{
			printf("\n ------------- i    and   j   vale is %d %d\n",i,j);
			if(j%(block_size/4)==0)
			{
				MatrixC=map_block("./MatrixC",2,i,j%(block_size/4));
				memset(MatrixC,0,block_size);
				index=0;
			}
			for(k=0;k<(nCols*4/block_size);k++)
			{
				MatrixA=map_block("./MatrixA",1,i,k);
				MatrixB=map_block("./MatrixB",1,j,k);
				MatrixC[index]+=block_by_block_multiply();
				munmap(MatrixB,block_size);
				munmap(MatrixA,block_size);
			}
			index++;

			if((j+1)%(block_size/4)==0)
			{

                              	int loc=0,w,buf=0;
				for(loc=0;loc<block_size/4;loc++)
				{ 
					buf=MatrixC[loc];
					//printf("%d ",buf);
 					w=write(fd,&buf,4);
				}
				munmap(MatrixC,block_size);

			}
	        }
	}

	close(fd);
}

int main(int argc,char **argv)
{
	if(argc==3)
	{
		nRows=atoi(argv[1]);block_size=atoi(argv[2]);
		
	}

	else if(argc==2)
	{
		nRows=atoi(argv[1]);
		printf("\nassuming that block size  as  2*1024*1024\n");block_size=2*1024*1024;
	}
	else if(argc==1)
	{
		printf("\nassuming that array size as 2*1024*1024 and block Size as 2*1024*1024\n");
		nRows=2*1024*1024;
		block_size=2*1024*1024;

	}
		nCols=nRows;
	if(nRows<2*1024*1024)
	block_size=nRows*4;
	padding=nRows%(block_size/4);//if nRows not power of 2
	if(padding!=0)
	padding=block_size/4-padding;


	//fillMatrix("./MatrixA");
	printf("\n\n Matrix A is......\n\n");
	int fd=open("./MatrixA",O_CREAT);
	close(fd);
	fd=open("./MatrixB",O_CREAT);
	close(fd);
	fd=open("./MatrixC",O_CREAT);
	close(fd);//
	//fillMatrix("./MatrixB");
	printf("\n\n Matrix B is ...........\n\n");
	//printMatrix("./MatrixB");
	//fillMatrix("./MatrixC");
	printf("\n\n Matric C.....\n\n");
	//printMatrix("./MatrixC");
	nRows=nRows;
	nCols=nRows+padding;//appending 0's when rwo is not multiple of page size	
	//printMatrix("./MatrixA");
	struct timeval tv_start,tv_end;
	gettimeofday(&tv_start,NULL);

	map_Matrix();
	gettimeofday(&tv_end,NULL);
	nCols=nCols-padding;
	padding=0;

	//printMatrix("./MatrixC");
	printf("\n\n-----------------------------------------------------------------------------------------------\n\n");
	
	printf("\n \n time taken is  %f sec ",(double)((tv_end.tv_sec-tv_start.tv_sec)+((tv_end.tv_usec-tv_start.tv_usec)/1000000)));
	return 0;
}
