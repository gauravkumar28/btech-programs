#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>
#include<iostream>
#include<malloc.h>
/* tbb related header files........*/
#include "tbb/tick_count.h"
#include "tbb/task_scheduler_init.h"
#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>
#include "tbb/scalable_allocator.h"

using namespace tbb;
using namespace std;
size_t vecSize;
float *vA,*vB,*vC;
size_t mapsize;

void fill_vector(float *buf)
{
for(size_t i=0;i<vecSize;i++)
{buf[i]=2.00f;
}
}
void print_vector(float *buf)
{
for(size_t i=0;i<vecSize;i++)
printf("%lf ",buf[i]);
printf("\n");
}
float *map_vector (float *vector,int vecSize)
{
size_t mapsize;
mapsize=vecSize *sizeof(float);
vector=(float*)malloc(mapsize);
return vector;
}

void free_mem(float *vector)
{
free(vector);
}

/* structure for vector vector multiplication using tbb */
struct ParVectorMult
{
size_t vecSize;
float *vC,*vA,*vB;
void operator () (const blocked_range <size_t > &r) const
{
int i;
for(i=r.begin();i!=r.end();++i)
{vC[i]=vA[i]*vB[i];
}
}
};
void par_vector_vector_multiply()
{
float sum=0.0;
ParVectorMult pmat;
pmat.vecSize=vecSize;
pmat.vA=vA;
pmat.vB=vB;
pmat.vC=vC;
parallel_for(tbb::blocked_range<size_t>(0,vecSize,1000),pmat);
for(int i=0;i<vecSize;++i)
sum+=vC[i];
vC[0]=sum;
}


int main(int argc,char *argv[])
{
if(argc!=2)
{
printf(" command error <vector size> ");
exit(1);
}
vecSize=atoi(argv[1]);
tbb::task_scheduler_init init;
vA=map_vector(vA,vecSize);
vB=map_vector(vB,vecSize);
vC=map_vector(vC,vecSize);
fill_vector(vA);
fill_vector(vB);
printf("Vector filled......");
tick_count t0=tick_count::now();
par_vector_vector_multiply();
tick_count t1=tick_count::now();
printf("Vector  multiplication Done  ..||");
printf("\n\t\t result : %lf",vC[0]);
printf("\n\t\t Vector Size : %ld",vecSize);
printf("\n\t\t Time taken to Perform: %lf Sec",(t1-t0).seconds());
free_mem(vA);
free_mem(vB);
free_mem(vC);
printf("\n Memory freed .........");
return 0;
}



