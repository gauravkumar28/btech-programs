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

int fA,fB,fC,chunk_size,nRows,nCols,sum=0;

int *MatrixA,*MatrixB,*MatrixC;

void fillMatrix(char *name)
{
FILE *fp=fopen(name,"w+");
if(fp==NULL)
{

perror("Error in opening file");
exit(1);
}
int i,j;
for(i=0;i<nRows;i++)
{

int x=2,nwrite;
nwrite=fwrite(&x,sizeof(int),1,fp);
assert(nwrite==1);


}
fclose(fp);
}

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
nread=fread(&val,sizeof(int),1,fp);
assert(nread==1);
printf("%d ",val);
}
printf("\n");

fclose(fp);
}





void setValue(int * a,int offset,int val)
{
a[offset]=val;
}


int getValue(const int * Matrix,int offset)
{
return Matrix[offset];
}


int  chunk_by_chunk_multiply()
{
size_t i,j,k;
int sum;

sum=0;
for(j=0;j<chunk_size/4;j++)
{
//printf("\n shyam\n");
sum+=MatrixA[j]*MatrixB[j];
}
//printf("\n shyam\n");
return sum;


}

int* map_matrix_chunk(char * name,int mode,int offset)
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

//for(i=0;i<chunk_size/4;i++)
long int cur_position =offset*chunk_size;
//printf("\n cur_position %ld\n",cur_position);
lseek(fd,cur_position,SEEK_SET);

void  *map_addr=NULL;
if(mode==1)
map_addr=mmap(0,chunk_size,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_HUGETLB |MAP_ANONYMOUS,fd,0);
else
map_addr=mmap(0,chunk_size,PROT_READ|PROT_WRITE,MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB,fd,0);
if(map_addr==MAP_FAILED)
{
perror("MMAP Error");exit(1);
}
int i,a;
int *buf=(int*)map_addr;
for(i=0;i<chunk_size/4;i++)
{

*(buf++)=2;

}
printf("\n ---------\n");
close(fd);
return map_addr;

}

void  map_Matrix()
{

int i,j,k,index;

for(i=0;i<(nRows*4)/chunk_size;i++)
{
/*
MatrixC=map_matrix_chunk("./MatrixC",2,i,j);
memset(MatrixC,0,chunk_size);
index=0;
}
for(k=0;k<(nRows*4/chunk_size);k++)
{

*/
MatrixA=map_matrix_chunk("./MatrixA",1,i);
printf("\n %d",*MatrixA);
MatrixB=map_matrix_chunk("./MatrixB",1,i);
sum+=chunk_by_chunk_multiply(k);
munmap(MatrixB,chunk_size);
munmap(MatrixA,chunk_size);
}
}

int main(int argc,char **argv)
{
if(argc==3)
{
nRows=atoi(argv[1]);chunk_size=atoi(argv[2]);
}

else if(argc==2)
{
nRows=atoi(argv[1]);
printf("\nWe assuming chunk size  as  4096\n");chunk_size=4096;
}
else if(argc==1)
{
printf("\n We assuming array size as 2*1024*1024 and Chunk Size as 2*1024*1024\n");
nRows=2*1024*1024;
chunk_size=2*1024*1024;

}
nCols=nRows;
//fillMatrix("./MatrixA");
printf("\n\n Matrix A is......\n\n");
//
//fillMatrix("./MatrixB");
printf("\n\n Matrix B is ...........\n\n");
fillMatrix("./MatrixC");
printf("\n\n Matric C.....\n\n");
//printMatrix("./MatrixC");
struct timeval tv_start,tv_end;
gettimeofday(&tv_start,NULL);
map_Matrix();
gettimeofday(&tv_end,NULL);
printf("\n %d\n",sum);
printMatrix("./MatrixA");
printMatrix("./MatrixB");
getchar();
printf("\n Time taken is %f\n",(double)(tv_end.tv_sec-tv_start.tv_sec)+(tv_end.tv_usec-tv_start.tv_usec)/1000000);
//printMatrix("./MatrixC");
/*
void *addr;

	addr = mmap(0, 10*1024*1024, PROT_READ|PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_HUGETLB, 0, 0);
	if (addr == MAP_FAILED) {
		perror("mmap");
		exit(1);
	}

	printf("Returned address is %p\n", addr);
getchar();
	munmap(addr, 10*1024*1024);*/
return 0;
}
