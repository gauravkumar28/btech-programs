#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>

long int offsetA=0,offsetB=0,offsetC=0;
long int sizeA,sizeB;
long int mem_access,Elem_block;
size_t nrows,nclos;
int rowSize,colSize;
int countA,countB;

int fda,fdb,fdc;

#define pagesize 4096
inline size_t getID(int i,int j)
{
assert(i>=0&&i<nrows);
assert(j>=0;j<ncols);
return i*nrows+j;
}


void fill_matrix0(char *fname)
{
FILE *fp=fopen(fname,"w+");
if(fp==NULL)
{
printf("Cannot open file %s:\n",fname);
return ;
}
size_t i,j;
int nwrite;
for(i=0;i<nrows;i++)
{
for(j=0;j<ncols;j++)
{
float val=0.0;
nwrite=fwrite(&val,sizeof(float),1,fp);
printf("%f \n",val);
assert(nwrite ==1);
}
}
fclose(fp);
}
void fill_matrix(char *fname)
{
FILE *fp=fopen(fname,"w+");
if(fp==NULL)
{
printf("Can not open file %s : \n",fname);
return ;
}
size_t i,j;
int nwrite;
for(i=0;i<nrows;i++)
{
for(j=0;j<ncols;j++)
{
size_t id=getID(i,j);
float val=id;
nwrite=fwrite(&val,sizeof(float),1,fp);
printf("%f \n",val);
assert(nwrite==1);
}
}
fclose(fp);
}
void fill_matrixT(char *fname)
{
FILE *fp=fopen(fname,"w+");
if(fp==NULL)
{
printf("Can not open file %s:\n",fname);
return ;
}
size_t i,j;
int nwrite;
for(i=0;i<nrows;i++)
{
for(j=0;j<ncols;j++)
{

size_t id=getID(i,j);
float val=id;
nwrite=fwrite(&val,sizeof(float),1,fp);
printf("%f \n",val);
assert(nwrite==1);
}
}
fclose(fp);
}
void multiply(float *mapA,float *mapB)
{
int SRowA,SRowB;
int SColA,SColB;
int ERowA,EColB;
int EColA,EColB;
float *mapC;
printf("row %d \n",rowsize);
SRowA=offsetA/rowSize;


