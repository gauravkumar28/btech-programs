/*
Project:NITW-SUMMER-PROJECT-2013-HPC-FTE
NAME:GAURAV KUMAR
AIM: use of mmap for handling huge data as we know by default page size of memory in linux system is 4096 so we can't copy more size data so we need to take chunk by chunk and perform operation we are using mmap and doing this 
matrix multiplication of large size using chunk by chunk
input: nRows  and chunk_size
output: resultent matrix
improvement: when i am mapping file  matrixc that is not automaticaly copied to matrixc . i don't know some bug might be there so i am
 copying data to matrix c which increase time complexity which can be improved 
performance was tasted for data upto size 100000 and it was working

note::  chunk_size should be multiple of 4096 and i am padding zero if row and column size is not multiple of chunk_size/4
4096  took  647sec
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

int chunk_size,nRows,nCols,padding;
int seek=0;

int *MatrixA,*MatrixB,*MatrixC;
//  input matrix......................
void fillMatrix(char *name)
{
FILE *fp=fopen(name,"w+");
    if(fp==NULL)
	{

	perror("Error in opening file");
	exit(1);
	}
int i,j;

//printf(" \n padding is %d\n",padding);
	for(i=0;i<nRows;i++)
		{
			for(j=0;j<nCols;j++)
				{
					int x=2,nwrite;
						nwrite=fwrite(&x,sizeof(int),1,fp);
							assert(nwrite==1);

				}
			for(j=0;j<padding;j++)
				{

					int x=0,nwrite;
						nwrite=fwrite(&x,sizeof(int),1,fp);
							assert(nwrite==1);



				}
			}
fclose(fp);
}

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

// chunk by chunk matrix multiply............

int  chunk_by_chunk_multiply()
{
size_t i,j,k;
int sum;

sum=0;
		for(j=0;j<chunk_size/4;j++)
			{
				sum+=MatrixA[j]*MatrixB[j];
			}
	return sum;


}




//mapping  chunk to memory






int* map_matrix_chunk(char * name,int mode,int rowindex,int colindex)
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

int cur_position =rowindex*nRows*4+colindex*chunk_size;
lseek(fd,cur_position,SEEK_SET);

	int *map_addr=NULL;
		if(mode==1)
			map_addr=mmap(NULL,chunk_size,PROT_READ,MAP_SHARED,fd,0);
		else if(mode==2)
			map_addr=mmap(NULL,chunk_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
				if(map_addr==MAP_FAILED)
					{
						perror("MMAP Error");exit(1);
					}
close(fd);
return map_addr;

}

/*

mapping matrix  chunk to memory  with different offset the previous fun
used for matrix A only

*/

int* map_matrix_chunk2(char * name,int mode,int rowindex,int colindex)
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

int cur_position =rowindex*4+colindex*chunk_size;
lseek(fd,cur_position,SEEK_SET);
int *map_addr=NULL;
				if(mode==1)
					map_addr=mmap(NULL,chunk_size,PROT_READ,MAP_SHARED,fd,0);
				else if(mode==2)
					map_addr=mmap(NULL,chunk_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
				if(map_addr==MAP_FAILED)
					{
						perror("MMAP Error");exit(1);
					}
close(fd);
return map_addr;

}

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
							//printf("\n ------------- i    and   j   vale is %d %d\n",i,j);
							if(j%(chunk_size/4)==0)
									{
										MatrixC=map_matrix_chunk2("./MatrixC",2,i,j%(chunk_size/4));
										memset(MatrixC,0,chunk_size);
										index=0;
									}
									for(k=0;k<(nCols*4/chunk_size);k++)
										{
											MatrixA=map_matrix_chunk2("./MatrixA",1,i,k);
											MatrixB=map_matrix_chunk("./MatrixB",1,j,k);
											MatrixC[index]+=chunk_by_chunk_multiply(k);
											munmap(MatrixB,chunk_size);
											munmap(MatrixA,chunk_size);
										}
											index++;

									if((j+1)%(chunk_size/4)==0)
										{

                                                                                    	int loc=0,w,buf=0;
											for(loc=0;loc<chunk_size/4;loc++)
											{     buf=MatrixC[loc];
//printf("%d ",buf);
 												w=write(fd,&buf,4);
											}
										munmap(MatrixC,chunk_size);

										}
						 }
                     		}

close(fd);
}

int main(int argc,char **argv)
{
	if(argc==3)
	{
			nRows=atoi(argv[1]);chunk_size=atoi(argv[2]);
		if(chunk_size&(chunk_size-1)!=0)
		{
			printf("\n Chunk_Size should be Power of 2\n");
			exit(1);
		}
	}

	else if(argc==2)
	{
			nRows=atoi(argv[1]);
			printf("\nWe assuming chunk size  as  4096\n");chunk_size=4096;
	}
	else if(argc==1)
	{
			printf("\n We assuming array size as 8192 and Chunk Size as 4096\n");
			nRows=8192;
			chunk_size=4096;

	}
		nCols=nRows;
padding=nRows%(chunk_size/4);//if nRows not power of 2
	if(padding!=0)
	padding=chunk_size/4-padding;

fillMatrix("./MatrixA");
printf("\n\n Matrix A is......\n\n");
//printMatrix("./MatrixA");
fillMatrix("./MatrixB");
printf("\n\n Matrix B is ...........\n\n");
//printMatrix("./MatrixB");
fillMatrix("./MatrixC");
printf("\n\n Matric C.....\n\n");
//printMatrix("./MatrixC");
nRows=nRows;
nCols=nRows+padding;//appaanding 0's when rwo is not multiple of page size

struct timeval tv_start,tv_end;
gettimeofday(&tv_start,NULL);

map_Matrix();
gettimeofday(&tv_end,NULL);
nCols=nCols-padding;
padding=0;

printMatrix("./MatrixC");
printf("\n\n-----------------------------------------------------------------------------------------------\n\n");

printf("\n \n time taken is  %f sec ",(double)((tv_end.tv_sec-tv_start.tv_sec)+((tv_end.tv_usec-tv_start.tv_usec)/1000000)));
return 0;
}
