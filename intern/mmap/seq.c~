#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/mman.h>
#include<unistd.h>
#include<string.h>
#include<assert.h>


#define MAP_RDONLY 1
#define MAP_RDWR 2


int fda,fdb,fdc,fds;
size_t nrows,ncols;
float *ma,*mb,*mc,*ms;
size_t mapsize;


inline size_t getID(int i,int j)
{

assert(i>=0&&i<nrows);
assert(j>=0&&j<ncols);
return i*nrows+j;
}
inline float getVal(const float *buf,int i,int j)
{
size_t id=getID(i,j);
return buf[id];
}
inline void setVal(float *buf,int i,int j,float val)
{
size_t id=getID(i,j);
buf[id]=val;
}

void fill_matrix(char *fname)
{
FILE *fp=fopen(fname,"w+");
if(fp==NULL)
{
printf("Cannot open fie %s:\n",fname);
exit(1);
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
assert(nwrite==1);

}


}
fclose(fp);
}

void printfile(const char *fname)
{
FILE *fp=fopen(fname,"r");
if(fp==NULL)
{
printf("Cannot open file %s:\n",fname);
return ;
}
size_t i,j;
float val;
for(i=0;i<nrows;i++)
{
for(j=0;j<ncols;j++)
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
for(i=0;i<nrows;i++)
{
for(j=0;j<ncols;j++)
{
val=getVal(buf,i,j);
printf("%lf ",val);
}
printf("\n\n");
}
}
float * map_matrix(char *fname,int mode,int nrows,int ncols,int *fileid)
{
int fd,stat;
size_t mapsize;
float *map_addr=NULL;
ncols=nrows;
mapsize=nrows*ncols*sizeof(float);
if(mode==MAP_RDONLY)
fd=open(fname,O_RDONLY);
if(mode==MAP_RDWR)
fd=open(fname,O_RDWR);
if(fd<0)
{
printf("Error: can't open file matrix %d \n",fd);
return NULL;
}
if(mode==MAP_RDONLY)
map_addr=(float*)mmap(0,mapsize,PROT_READ,MAP_SHARED,fd,0);
if(mode==MAP_RDWR)
map_addr=(float*)mmap(0,mapsize,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
if(map_addr==MAP_FAILED)
{printf("Error : mmap failed \n");
exit(1);
}
*fileid=fd;
return map_addr;
}

void par_vector_vector_multiply()
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
aik=getVal(ma,i,k);
bkj=getVal(mb,k,j);
sum+=aik*bkj;
}
setVal(mc,i,j,sum);
}
}
}
int main(int argc,char *argv[])
{
if(argc!=2)
{
printf("No of rows not specified \n");
return 1;
}
struct timeval tv,tv1;
nrows=atoi(argv[1]);
ncols=nrows;
mapsize=nrows*ncols*sizeof(float);
fill_matrix("./matrixA");
fill_matrix("./matrixB");
fill_matrix("./matrixC");
printf("Matrix filled \n");
ma=map_matrix("./matrixA",MAP_RDONLY,nrows,ncols,&fda);
mb=map_matrix("./matrixB",MAP_RDONLY,nrows,ncols,&fdb);
mc=map_matrix("./matrixC",MAP_RDWR,nrows,ncols,&fdc);
gettimeofday(&tv,NULL);
par_vector_vector_multiply();
gettimeofday(&tv1,NULL);
double tm=tv1.tv_sec-tv.tv_sec+(tv1.tv_usec-tv.tv_usec)*0.000001;
printf("%lf , %lf \n",tv1.tv_sec+0.0,tv.tv_sec+0.0);
printf("\n time taken is %lf  seconds \n",tm);

printf("Matrix A is ..\n");
print_matrix(ma);
printf("Matrix B is ..\n");
print_matrix(mb);
printf("Matrix C is ..\n");
print_matrix(mc);
munmap(ma,mapsize);
munmap(mb,mapsize);
munmap(mc,mapsize);
close(fda);
close(fdb);
close(fdc);
return 0;
}






