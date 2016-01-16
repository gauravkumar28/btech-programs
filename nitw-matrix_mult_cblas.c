/*
Project:NITW-SUMMER-PROJECT-2013-HPC-FTE
NAME:GAURAV KUMAR
AIM: use of dgemm-cblas and mmap to multiply two matrices of large size
input: nRows  and chunk_size in bytes
output: resultant matrix and G_Flops computation
limitation:working for matrix row size being a power of 2

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
#include<malloc.h>
#include<omp.h>
/* CBLAS header file inclusion*/
#include <mkl.h>
//#include <cblas.h>


#define EPS 1.0e-12 /* threshhold aprrox epsilion value */ 
#define block_of_row 512
double alpha = 1.0, beta = 0.0;
float  *elapsedTime; /* holds total elapsed time */
double Gflops; /* holds FLOPS */
double Tsec_cpu=0.0,Tsec_gpu=0.0; /* holds time taken for computation on CPU */
struct timeval tv_start, tv_end; /* variable to hold start / end time for CPU*/

int chunk_size,nRows,nCols,padding;
int seek=0;
int *MatrixA,*MatrixB,*MatrixC;
double *bufferA,*bufferB,*bufferC;


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
	int sum=0;

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
 		fd=open(name,O_RDWR,0666);
	
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



void domult(int a,int b)
{
	int i,j,k;
	float sum;	
      	gettimeofday(&tv_start,0);

	printf("\nbufferA having index %d\t bufferB having index %d\n",a/block_of_row,b/block_of_row);

        /***** Performs operation using CBLAS DGEMM*******/
  
	#pragma omp parallel private(nRows)  
        cblas_dgemm (CblasRowMajor, CblasNoTrans, CblasNoTrans, block_of_row, block_of_row , nRows, 1.0, bufferA, nRows , bufferB , block_of_row, 0.0, bufferC, block_of_row);
       /*for(i=0;i<block_of_row;i++)
{
for(j=0;j<block_of_row;j++)
{sum=0.0;
for(k=0;k<nRows;k++)
sum+=bufferA[i*block_of_row+k]*bufferB[j*block_of_row+k];
bufferC[i*block_of_row+j]=sum;
}
}*/
	 gettimeofday(&tv_end,0);



        /* compute total time taken for computation on CPU */
        Tsec_cpu = ((double)tv_end.tv_sec + (((double) (tv_end.tv_usec) /1000000.0))) - ((double)tv_start.tv_sec + (((double) (tv_start.tv_usec) /1000000.0)))  ;


        /* Compute Gflops */
         Gflops= ( 1.0e-3 * (1.0e-6 * ((2. * block_of_row *nRows * block_of_row) /Tsec_cpu))) ;
//printf("\n \n no of GigaFlops  used  is %f\n\n",Gflops);
	 printf("\n cpu time is: \t %.8lf  \t\t\tGiga Flops is: %.8lf", (Tsec_cpu )  , Gflops );
}



void  map_Matrix()
{
	int i,j,k,index,l;
	int fd=open("./MatrixC",O_RDWR);
	if(fd==-1)
	{
		perror("File not opened ");
		exit(1);

	}

	bufferA=(double*)malloc(sizeof(double)*block_of_row*nRows);
	bufferB=(double*)malloc(sizeof(double)*block_of_row*nCols);
	bufferC=(double*)malloc(sizeof(double)*block_of_row*block_of_row);

	for(i=0;i<(nRows);i=i+block_of_row)
	{
					
		for(j=0;j<(nCols);j=j+block_of_row)
		{
							
			int indexA=0,indexB=0;
                        for(l=0;l<block_of_row;l++)
			{
				for(k=0;k<(nCols*4/chunk_size);k++)
				{
					int a;
					MatrixA=map_matrix_chunk2("./MatrixA",1,i+l,k);
					MatrixB=map_matrix_chunk("./MatrixB",1,j+l,k);
					for(a=0;a<chunk_size/4;a++)
					{
						bufferA[indexA++]=MatrixA[a];						
				   		bufferB[indexB++]=MatrixB[a];
							
					}
											
					munmap(MatrixB,chunk_size);
					munmap(MatrixA,chunk_size);
				 }
			}
											

			domult(i,j);
			int p,q,buf;
			for(p=0;p<block_of_row;p++)
			{
				lseek(fd,((i+p)*nRows*4+j*4),SEEK_SET);
				for(q=0;q<block_of_row;q++)
				{
					buf=(int)bufferC[p*block_of_row+q];
					write(fd,&buf,4);

				}
			}
		}
	}

	close(fd);
}











int main(int argc,char **argv)
{
	if(argc==3)
	{
		nRows=atoi(argv[1]);
		chunk_size=atoi(argv[2]);
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

	fillMatrix("./MatrixB");
	printf("\n\n Matrix B is ...........\n\n");
	fillMatrix("./MatrixC");
	printf("\n\n Matric C.....\n\n");

	nCols=nRows+padding;//appending 0's when rwo is not multiple of page size

	struct timeval tv_start1,tv_end1;
	gettimeofday(&tv_start1,NULL);

	map_Matrix();
	gettimeofday(&tv_end1,NULL);
	nCols=nCols-padding;
	padding=0;
	
  	Tsec_cpu = ((double)tv_end1.tv_sec + (((double) (tv_end1.tv_usec) /1000000.0))) - ((double)tv_start1.tv_sec + (((double) (tv_start1.tv_usec) /1000000.0)))  ;

	Gflops= ( 1.0e-3 * (1.0e-6 * ((2.0 * block_of_row *nRows * block_of_row) /Tsec_cpu))) ;
       // printMatrix("./MatrixC");
	printf("\n\n-----------------------------------------------------------------------------------------------\n\n");

	printf("\n \n time taken is  %f sec \n",(double)((tv_end1.tv_sec-tv_start1.tv_sec)+((tv_end1.tv_usec-tv_start1.tv_usec)*0.000001)));
//	printf("\n \n no of GigaFlops  used  is %f\n\n",Gflops);
	free(bufferA);
	free(bufferB);
	free(bufferC);
	unlink("./MatrixA");
	unlink("./MatrixB");
	unlink("./MatrixC");
	return 0;
}
