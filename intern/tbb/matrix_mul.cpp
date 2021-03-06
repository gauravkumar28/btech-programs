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

#include "tbb/tick_count.h"
#include "tbb/task_scheduler_init.h"
#include <tbb/parallel_for.h>
#include <tbb/blocked_range2d.h>
#include "tbb/scalable_allocator.h"

using namespace tbb;
using namespace std;
size_t nRows,nColms;
float **mA,**mB,**mR;
size_t mapSize;
size_t mapCsize;

void fill_matrix(float **buf)
{

for(size_t i=0;i<nRows;i++)
{
for(size_t j=0;j<nColms;j++)
{
buf[i][j]=2.00f;
}
}
}

void print_matrix(float **buf)
{
for(size_t i=0;i<nRows;i++)
{
for(size_t j=0;j<nColms;j++)
{
printf("%lf ",buf[i][j]);
}
printf("\n");
}
}


float **map_matrix(float **matrix,int nRows,int nColms)
{
size_t mapSize;
size_t mapCsize;
mapSize=nRows*sizeof(float*);
mapCsize=nColms*sizeof(float);
matrix=(float**)malloc(mapSize);
for(size_t i=0;i<nRows;i++)
matrix[i]=(float*)malloc(mapCsize);
return matrix;
}
void free_mem(float **matrix)
{
free(matrix);
}
struct ParMatrixMult
{
size_t nRows,nColms;
float **mR,**mA,**mB;
void operator () (const blocked_range2d <size_t,size_t>&r)const
{
int i,j,k;
float sum;
for(i=r.rows().begin();i<r.rows().end();++i)
{
for(j=r.cols().begin();j<r.cols().end();++j)
{
sum=0.0;
for(k=0;k<nColms;++k)
{
sum+=mA[i][k]*mB[k][j];
}
mR[i][j]=sum;
}
}
}
};

void par_matrix_matrix_multiply()
{
ParMatrixMult pmat;
pmat.nRows=nRows;
pmat.nColms=nColms;
pmat.mA=mA;
pmat.mB=mB;
pmat.mR=mR;
parallel_for(tbb::blocked_range2d<size_t,size_t >(0,nRows,0,nColms),pmat);

}

int main(int argc,char *argv[])
{

if(argc!=2)
{
printf("comman error <matrix size> \n");exit(1);
}
nRows=atoi(argv[1]);
nColms=nRows;
tbb::task_scheduler_init init;
mA=map_matrix(mA,nRows,nColms);
mB=map_matrix(mB,nRows,nColms);
mR=map_matrix(mR,nRows,nColms);
fill_matrix(mA);
fill_matrix(mB);
tick_count t0=tick_count::now();
par_matrix_matrix_multiply();
tick_count t1=tick_count::now();
printf("Multiplication Done...");
printf("\n\t\t Matrix Size is %d",nRows);
printf("\n\t\t time taken to perform multiplication is...%lf sec\n",(t1-t0).seconds());

for(int i=0;i<nRows;i++)
{
for(int j=0;j<nColms;j++)
{
printf("\t %lf",mR[i][j]);
}
printf("\n");
}

free_mem(mA);
free_mem(mB);
free_mem(mR);
return 0;
}
