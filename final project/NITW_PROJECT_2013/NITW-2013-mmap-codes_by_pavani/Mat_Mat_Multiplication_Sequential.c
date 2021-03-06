/*

NITW students -Summer Project 2013 in HPC-FTE

AIM   :Matrix Multiplication by mapping the whole matrix into memory
INPUT :Input for the two matrices to be multiplied A and B are read from files matrixA,matrixB
       Number of rows of the matrices to be multiplied is sent as argument
OUTPUT:Output of the multiplication is stored in another file matrixC

By using mmap() for mapping the files in which data to be multiplied is stored as well as the output, time is saved on 
memory access(i.e it is lesser than that when we try to read from the disk directly).

Constraint here is on how much can we map to the memory.If the memory cant map three times the mapsize(i.e no_of_rows*no_of_cols*size_of_datatype(here we consider as float)) then the multiplication will fail


*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

#define MAP_RDONLY   1
#define MAP_RDWR     2

int fda, fdb, fdc,fds;
size_t nrows, ncols;
float *mapA, *mapB, *mapC;
size_t mapsize;



inline size_t getID (int i,int j)
{
  assert (i >= 0 && i < nrows);
  assert (j >= 0 && j < ncols);

  return i * nrows + j;
}


inline float getVal (const float *buf, int i, int j)
{
  size_t id = getID (i, j);
  return buf[id];
}

inline void setVal (float *buf, int i, int j, float val)
{
  size_t id = getID (i, j);
  buf[id] = val;
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
   for ( i = 0; i < nrows; i++)
    {
     	 for (j = 0; j < nrows; j++)
	 {
	 	 size_t id = getID (i, j);
	 	 float val = id;
	 	 nwrite = fwrite (&val, sizeof (float), 1, fp);
	 	 assert (nwrite == 1);
	 }
    }
  fclose (fp);
}



void print_file(const char *fname)
{
	FILE *fp=fopen(fname,"r");
	if(fp==NULL)
	{
		printf("Cannot open file %s:\n",fname);
		return;
	}

	size_t i,j;
	float val;

	for(i=0;i<nrows;i++)
	{
		for( j=0;j<ncols;j++)
		{
			fread(&val,sizeof(float),1,fp);
			printf("%lf ",val);
		}
	printf("\n");
	}
}

void print_matrix(const float *buf)
{
	float val;
	size_t i,j;
  	for (i = 0; i < nrows; i++)
    	{
      		for ( j = 0; j < ncols; j++)
		{
	  		val = getVal (buf, i, j);
	 		printf ("%lf ", val);
		}
      		printf ("\n \n");
    	}
}





float *map_matrix(char *fname, int mode, int nrows, int ncols, int *fileid)
{

	int fd, stat;
	size_t mapsize;
	float *map_addr = NULL;

  	ncols = nrows;
  	mapsize = nrows * ncols * sizeof (float);

	if (mode == MAP_RDONLY)
	    fd = open (fname, O_RDONLY);  
	if (mode == MAP_RDWR)
	    fd = open (fname, O_RDWR);

	if (fd <= 0)
 	{
      		printf ("Error: Can't open file matrix %d \n",fd);
      		return NULL;
    	}

	if(mode==MAP_RDONLY)
		map_addr=(float *)mmap(0,mapsize,PROT_READ,MAP_SHARED,fd,0);

	if(mode==MAP_RDWR)
		map_addr=(float *) mmap (0, mapsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	if (map_addr == MAP_FAILED)
   	 {
      		printf ("Error: mmap failed \n");
      		exit (0);
      		return NULL;
    	}
  	*fileid = fd;

  return map_addr;
}


void Mat_Mat_Multiplication_Sequential()
{
int i,j,k;
int sum,aik,bkj;
	for(i=0;i<nrows;i++)
	{
		for(j=0;j<ncols;j++)
		{
			sum=0.0;
			for(k=0;k<ncols;k++)
			{
				aik=getVal(mapA,i,k);
				bkj=getVal(mapB,k,j);
				sum+=aik*bkj;
			}
			setVal(mapC,i,j,sum);
		}
	}
}




int main(int argc, char *argv[])
{
	
	// One argument is required to specify the number of rows 
	if(argc!=2)
	{
		printf("No of rows not specified \n");
		return 1;
	}
	
	struct timeval tv,tv1;
	

	
	nrows=atoi(argv[1]);
	ncols=nrows; //Assuming it is a square matrix 
	mapsize=nrows*ncols*sizeof(float);

	fill_matrix("./matrixA");
	fill_matrix("./matrixB");
	fill_matrix("./matrixC");

	printf("Matrix filled \n");



	 mapA = map_matrix ("./matrixA", MAP_RDONLY, nrows, ncols, &fda);  //mapping the entire file A to memory
  	 mapB = map_matrix ("./matrixB", MAP_RDONLY, nrows, ncols, &fdb);  //mapping the entire file B to memory
	 mapC = map_matrix ("./matrixC", MAP_RDWR, nrows, ncols, &fdc);    //mapping the entire file C to memory
	
	gettimeofday(&tv,NULL);
	Mat_Mat_Multiplication_Sequential();
	gettimeofday(&tv1,NULL);

	double diff_in_usec;
	if(tv1.tv_usec>tv.tv_usec)
		diff_in_usec=tv1.tv_usec-tv.tv_usec;

	else 
		diff_in_usec=tv.tv_usec-tv1.tv_usec;
	
	printf("time taken is %lf  seconds %lf microseconds\n",(tv1.tv_sec-tv.tv_sec)+0.0,diff_in_usec);
	
	printf("matrix C is \n");
	print_matrix(mapC);

	printf("time taken is %lf  seconds %lf microseconds\n",(tv1.tv_sec-tv.tv_sec)+0.0,diff_in_usec);
	
	munmap (mapA, mapsize);
  	munmap (mapB, mapsize);
  	munmap (mapC, mapsize);



  close (fda);
  close (fdb);
  close (fdc);

return 0;

}

	
	



	



