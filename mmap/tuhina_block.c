/*
NITW SUMMER PROJECT 2013 HPC-FTE
AIM:To multiply two matrix accessing data block by block
INPUT:Two files matrixA,matrixB which store the two matrix to be multiplied 
OUTPUT:A file matrixC

A minimum of 4 pages are required...
The arguments that are given to the program are matrix size and no of bytes available for computation

From the memory data is braught block by block according to pages allocated per matrix,
These two blocks are multiplied and hence C is filled

in matrixA and matrixB i hav given value 1 bt any value can be given


*/
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include<error.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>


long int offsetA=0,offsetB=0,offsetC=0;
long int  sizeA,sizeB;
long int mem_access,Elem_block;
size_t nrows, ncols;
int rowSize,colSize;
int countA,countB;
int fda,fdb,fdc;
int no_access=0,pages_reqd_matrix=0;
int pages_per_matrix_alloc;
float temp[1024];
int page=0;


#define page_size 2*1024*1024

inline size_t getID (int i,int j)
{
  assert (i >= 0 && i < nrows);
  assert (j >= 0 && j < ncols);

  return i * nrows + j;
}



void fill_matrix0(char *fname)
{
	FILE *fp=fopen(fname,"w+");
  	if(fp==NULL)
  	{
		printf("Cannot open file %s:\n",fname);
		return;
  	}

   size_t i,j;
   int nwrite;
   for ( i = 0; i < nrows; i++)
    {
     	 for (j = 0; j < ncols; j++)
	 {
		float val=0;
		nwrite = fwrite (&val, sizeof (float), 1, fp);
		//printf("%f \n",val);
	 	assert (nwrite == 1);
	 }
    }

fclose(fp);
}


void fill_matrix(char *fname)
{
  FILE *fp=fopen(fname,"w+");
  if(fp==NULL)
  {
	printf("Cannot open file %s:\n",fname);
	return;
  }

   size_t i,j;
   int nwrite;
   for ( i = 0; i<nrows; i++)
    {
     	 for (j = 0; j < ncols; j++)
	 {
	 	// size_t id = getID (i, j);
		int id=j+1;
	 	 float val = id;
	 	 nwrite = fwrite (&val, sizeof (float), 1, fp);
		 //printf("%f \n",val);
	 	 assert (nwrite == 1);
	 }
    }
fclose(fp);
 
}

void fill_matrixT(char *fname)
{
  FILE *fp=fopen(fname,"w+");
  if(fp==NULL)
  {
	printf("Cannot open file %s:\n",fname);
	return;
  }

   size_t i,j;
   int nwrite;
   for ( j = 0; j<ncols; j++)
    {
     	 for (i = 0; i < nrows; i++)
	 {
	 	//size_t id = getID (i, j);
		int id=j+1;
	 	 float val = id;
	 	 nwrite = fwrite (&val, sizeof (float), 1, fp);
		 //printf("%f \n",val);
	 	 assert (nwrite == 1);
	 }
    }
  fclose(fp);
}

void print_matrix(char *fname)
{
	int count=no_access;
	int fd=open(fname,O_RDONLY);
	int offset=0;
	int elements;
	int ct=0;
	float *map,*t;
	int mem_access,i,j;
	printf("count %d \n",count);
	while(count!=0)
	{
		if(count==1)
		{
			mem_access=sizeA-offset;
			//printf("mem_access %d \n",mem_access);sleep(1);
		}
		
		else 
			mem_access=pages_per_matrix_alloc*page_size;
			
			map=(float *)mmap(0,mem_access,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_HUGETLB |MAP_ANONYMOUS,fd,offset);
			if(map==MAP_FAILED)
			{
				printf("mapping failed  \n");
				exit(1);
				return;
			}
		
		elements=mem_access/4;
		t=map;
		for(i=0;i<elements;i++)
		{
			// printf("%f ",*t);
			*t=2;
			t++;ct++;
			if(ct%nrows==0)
			printf("\n****************\n");
		}
		offset+=mem_access;
		munmap(map,mem_access);
		count--;
		
		
	}

	
	
close(fd);	
	
}














void multiply(float *mapA,float *mapB, int mem_accessA,int mem_accessB)
{
	int SRowA,SRowB;
	int SColA,SColB;
	int ERowA,ERowB;
	int EColA,EColB;
	float *mapC;
	int fdc=open("./matrixC",O_RDWR);
	int k=0,l=0;

	
	//print_matrix("./matrixC");
	
	
	SRowA=(offsetA/rowSize);
	SColA=(offsetA%rowSize)/4;
	//if(SColA!=0) { SRowA=SRowA-1;}
	
	
	ERowA=(offsetA+mem_accessA-4)/rowSize;
	EColA=((offsetA+mem_accessA-4)%rowSize)/4;
	
	

	EColB=(offsetB+mem_accessB-4)/rowSize;
	ERowB=((offsetB+mem_accessB-4)%rowSize)/4;
	

//	if(EColB!=(nrows-1))
	 //EColB-=1;		
	
	SColB=offsetB/rowSize;
	SRowB=(offsetB%rowSize)/4;
	//if(SRowB!=0) { SColB-=1;}

	int i,j,n,offC;
	float *t=mapB;
	float *s=mapA;

	offC=0;
	int h=SRowA;
	int cntA=0;
	int cntB=0;
	float sum=0;	
	int y;
	
	

	//if(EColA!=ncols-1)
		//ERowA-=1;

	//if(ERowB!=nrows-1)
		//EColB-=1;

	int no_of_rows=mem_accessA/rowSize;
	
	int no_of_cols=mem_accessB/rowSize;
	if(mem_accessA%rowSize!=0) no_of_rows+=1;
	if(mem_accessB%rowSize!=0) no_of_cols+=1;
	//if(SColB==0) no_of_cols+=1;
	int rowbs=0,rowbe=0,colas=0,colae=0;
	float *tempA,*tempB,*pos_aik,*pos_bkj;

	//printf("SRowA %d SColA %d ERowA %d EColA %d \n SRowB %d SColB %d ERowB %d EColB %d \n no_of_rows %d no_of_cols %d \n",SRowA,SColA,ERowA,EColA,SRowB,SColB,ERowB,EColB,no_of_rows,no_of_cols);//scanf("%d",&y);
	//scanf("%d",&y);
	
	tempA=mapA;
	for(i=0;i<no_of_rows;i++)
	{
		colas=0;
		colae=ncols;

		if(i==0)
			colas=SColA;
		
		if(i==(no_of_rows-1))
			{ colae=EColA;}//printf("i is %d\n colae %d \n", i,colae);}//scanf("%d",&y);}

		for(j=0;j<no_of_cols;j++)
			temp[j]=0;

			tempB=mapB;

		for(j=0;j<no_of_cols;j++)
		{
			rowbs=0;
			rowbe=nrows;
			if(j==0)
			{
				rowbs=SRowB;
			}
			if(j==(no_of_cols-1))
			{
				rowbe=(ERowB);
				//printf("j is %d\n rowbe %d \n", j,rowbe);
				//printf("SRowA %d SColA %d ERowA %d EColA %d \n SRowB %d SColB %d ERowB %d EColB %d \n no_of_rows %d no_of_cols %d \n",SRowA,SColA,ERowA,EColA,SRowB,SColB,ERowB,EColB,no_of_rows,no_of_cols);scanf("%d",&y);
			}
			


			for(k=0;k<nrows;k++)
			{
				if((k>=colas && k<=colae) &&(k>=rowbs && k<=rowbe))
				{
					pos_aik=tempA+(k-colas);
					pos_bkj=tempB+(k-rowbs);

					
					float val=(*pos_aik)*(*pos_bkj);
					
				/*	if(i==(no_of_rows-1)||j==(no_of_cols-1)||j==0|| i==0)
					{ printf("i val %f %d  j val %f j %d\n",*pos_aik,i,*pos_bkj,j);
					  printf("$$$$$$$$$$$$$ k is %d \n",k);
					  if(k==rowbe||k==colas||k==rowbs||k==colae) scanf("%d",&y);
						
					   int a,b;
					 // sleep(2);
					  //printf("pos_aik %ld pos_bik %ld \n");
					 }
				*/

					
					temp[j]+=val;
					

					
				}
			}
			
			tempB+=(nrows-rowbs);
			
		}
		
		int prev_page=0;
		mem_access=page_size;
		for(l=0;l<no_of_cols;l++)
		{	

			int pageC;
			
			 pageC=((SRowA+i)*rowSize)+((SColB+l)*sizeof(float));

					
			offC=pageC/page_size;
			offC=offC*page_size;
			
			if(l==0 || prev_page!=offC)
			{
				if(l!=0)
				{
					munmap(mapC,mem_access);
					//perror("unmapping c \n");
				}
				mapC=(float*)mmap(0,mem_access,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_HUGETLB |MAP_ANONYMOUS,fdc,offC);
				//perror("mapping c \n");
				if(mapC==MAP_FAILED)
				{	
					printf("off %d mem_access %ld \n",offC,mem_access);
					printf(" i  %d \n, pageC %d \n %d SRowA \n %d SColB \n l %d \n",i,pageC,SRowA,SRowB,l);
					printf("mapping failed C %d \n",offC);exit(1);
					return;
				}

				
			}

			int off=(pageC-offC)/4;
			float *h=mapC;
			h=h+off;
			*h+=temp[l];
			
			/*if(l==0||l==no_of_cols-1)
			{	
				int m;
				printf("value already present %f \n",*h);
				printf("temp[%d] %f \n",l,temp[l]);
				printf("off %d mem_access %ld \n",offC,mem_access);
				printf(" i  %d \n, pageC %d \n %d SRowA..preA %d \n %d SColB \n l %d  preB %d \n",i,pageC,SRowA,SRowA+i,SColB,l,SColB+l);
				printf("rowC %d \t col C %d \n",pageC/rowSize,(pageC%rowSize)/4);
				printf("njaksnszna\n");//scanf("%d",&y);//sleep(1);
				//if((pageC/rowSize)==39||((pageC%rowSize)/4)==39){ printf("njaksnszna\n"); scanf("%d",&y);}
//}
				//scanf("%d",&m);
				
			}*/
			prev_page=offC;
			
		}
		
		
		tempA+=(ncols-colas);
	}		
			
		
	
munmap(mapC,mem_access);
//perror("unmap...c");
	
close(fdc);					
}			


	


void vector_multiply(char *fnameA,char *fnameB,char *fnameC)
{
	offsetA=0;
	offsetB=0;
	offsetC=0;

	int i,j;
	countA=no_access;
	countB=countA;
	int t=countB;
	int cntA=0,cntB=0;
	fda=open(fnameA,O_RDONLY);
	fdb=open(fnameB,O_RDONLY);
	int mem_accessA=0,mem_accessB=0;
	//fdc=open(fnameC,O_RDWR);
	

	float *mapA,*mapB;
	
	
	while(countA!=0)
	{
		if(countA==1)
		{
			mem_accessA=sizeA-offsetA;
			//printf("mem_accessA %d \n",mem_accessA);sleep(2);
		}
		
		else 
			mem_accessA=pages_per_matrix_alloc*page_size;
			//if(offsetA>(page*page_size)){ printf("next page \n");page++;}
			mapA=(float *)mmap(0,mem_accessA,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_HUGETLB |MAP_ANONYMOUS,fda,offsetA);
		if(mapA==MAP_FAILED)
		{
			printf("mapping failed A \n");
			exit(1);
			return;
		}

		t=countB;
		cntB=0;	
		offsetB=0; 
		while(t!=0 && offsetB<=sizeA)
		{
			
			mem_accessB=pages_per_matrix_alloc*page_size;
			if(t==1)
				{ mem_accessB=sizeB-offsetB;
				  
				}
			

			mapB=(float *)mmap(0,mem_accessB,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_HUGETLB |MAP_ANONYMOUS,fdb,offsetB);
			if(mapB==MAP_FAILED)
			{
				printf("mapping failed B \n");
				exit(1);
				return;
			}
			
			multiply(mapA,mapB,mem_accessA,mem_accessB);
			munmap(mapB,mem_accessB);
			
			offsetB+=mem_accessB;
			
			t--;
		}
		offsetA+=mem_accessA;
		munmap(mapA,mem_access);
		
		countA--;
	}

	//printf("done \n");
	close(fda);
	close(fdb);
}


void pad(char *fname,int padding)
{
	
	FILE *fp=fopen(fname,"r+");
	fseek(fp,0,SEEK_END);
	float val =0;
	size_t nwrite;
	int i;
	for(i=0;i<padding-1;i++)
	{
	 	nwrite = fwrite (&val, sizeof (float), 1, fp);
	}
	fclose(fp);
			
}
	







int main(int argc ,char *argv[])
{
	
	if(argc!=3)
	{
		printf("size of matrix,memory size not specified \n");
		return 0;
	}

	nrows=atoi(argv[1]);
	ncols=nrows;

	int mem_size=atoi(argv[2]);  // size of memory available
	int no_of_pages= mem_size/page_size;
	printf("no of pages totally available %d \n",no_of_pages);
	if(no_of_pages<4)
	{
		printf("Not enough pages present\n");
		return 0;
	}

	pages_per_matrix_alloc=no_of_pages/4; // each for matrix A B C and for computation  
	
	
	//Elem_block=mem_access/4; //elements per block

	fill_matrix("./matrixA");
	fill_matrixT("./matrixB");
	fill_matrix0("./matrixC");
	struct timeval tv,tv1;
	printf("done filling \n");
	
	sizeA=sizeof(float)*nrows*ncols;
	sizeB=sizeA;
	no_access=0;
	pages_reqd_matrix=0;

	pages_reqd_matrix=sizeA/page_size;
	if(sizeA%page_size!=0)
		pages_reqd_matrix+=1;
	printf("pages_reqd_matrix- %d \n pages_per_matrix_alloc %d \n",pages_reqd_matrix,pages_per_matrix_alloc);
	no_access=pages_reqd_matrix/pages_per_matrix_alloc;
	
	int padding=0;	
	if(pages_reqd_matrix%pages_per_matrix_alloc!=0)
	{
		no_access+=1;
		printf("no access %d \n",no_access);
		padding=pages_per_matrix_alloc*page_size-((pages_reqd_matrix%pages_per_matrix_alloc)*page_size);
		printf("padding reqd is %d \n",padding);

		
	}

	//int l=pages_reqd_matrix-1;	
	//int left=page_size-(sizeA-((l)*page_size));
	//padding+=left;
	padding+=4;
	//padding+=page_size*pages_per_matrix_alloc;
	
	pad("./matrixA",padding);
	pad("./matrixB",padding);
	pad("./matrixC",padding);

	print_matrix("./matrixB");sleep(20);
	
	rowSize=sizeof(float)*nrows;
	colSize=rowSize;
	printf("abt to multiply \n");
	gettimeofday(&tv,NULL);

	vector_multiply("./matrixA","./matrixB","./matrixC");
	
	gettimeofday(&tv1,NULL);

	double tm=tv1.tv_sec-tv.tv_sec+(tv1.tv_usec-tv.tv_usec)*0.000001;
	long int diff;
	if(tv1.tv_usec>tv.tv_usec)
		diff=tv1.tv_usec-tv.tv_usec;
	else
		diff=tv.tv_usec-tv1.tv_usec;
	printf("%lf , %lf \n",tv1.tv_sec+0.0,tv.tv_sec+0.0);
	printf("time taken is %ld seconds.%ld  micro_sec\n",tv1.tv_sec-tv.tv_sec,diff);	

	printf("multiplied \n");
	sleep(20);
	//print_matrix("./matrixA");sleep(10);
	print_matrix("./matrixC");	
	printf("\ntime taken is %ld seconds.%ld  micro_sec\n",tv1.tv_sec-tv.tv_sec,diff);

	return 0;
}
	
