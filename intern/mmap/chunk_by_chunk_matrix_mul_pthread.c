/* use of mmap   
aim : matrix multiplication of large size using chunk by chunk with pthread
input: nRows ,nCols and chunk_size
output: resultent matrix

*/


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
#include<pthread.h>

pthread_t *tid;

pthread_mutex_t lock;


int fA,fB,fC,chunk_size,nRows,nCols,padding,i,j,k,fd;
int seek=0;

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
padding=nRows%(chunk_size/4);
if(padding!=0)
padding=chunk_size/4-padding;
printf(" \n padding is %d\n",padding);
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
//assert(nread==1);
printf("%d ",val);

}
for(j=0;j<padding;j++)
{

nread=fread(&val,sizeof(int),1,fp);
//assert(nread==1);
printf("%d ",val);



}

printf("\n");
}

fclose(fp);
}

void printresult(char * name,int index)
{int i ,buf;
int fd=open(name,O_RDONLY);
lseek(fd,index,0);
for(i=0;i<chunk_size/4;i++)
{
read(fd,&buf,4);printf("%d ",buf);
}
close(fd);
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
sum+=MatrixA[j]*MatrixB[j];
}
return sum;


}
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
//printf(" %s %d cur position\n",name,cur_position);
lseek(fd,cur_position,SEEK_SET);

int *map_addr=NULL;
if(mode==1)
map_addr=mmap(NULL,chunk_size,PROT_READ,MAP_SHARED,fd,0);
else if(mode==2)
map_addr=mmap(NULL,chunk_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
if(map_addr==MAP_FAILED)
{
perror("MMAP Error");exit(1);}
/*int i=0;
for(i=0;i<chunk_size/4;i++)
printf("%d ",map_addr[i]);
scanf("%d",&i);
*/
close(fd);
return map_addr;

}
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
//printf("%s %d cur position from fun 2\n",name,cur_position);
lseek(fd,cur_position,SEEK_SET);
int *map_addr=NULL;
if(mode==1)
map_addr=mmap(NULL,chunk_size,PROT_READ,MAP_SHARED,fd,0);
else if(mode==2)
map_addr=mmap(NULL,chunk_size,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
if(map_addr==MAP_FAILED)
{
perror("MMAP Error");exit(1);}
close(fd);
return map_addr;

}
void *doWork(void * arg)
{
int i=*(int *)arg;
int index=0;
for(j=0;j<(nCols);j++)
{







printf("\n ------------- i    and   j   vale is %d %d\n",i,j);
if(j%(chunk_size/4)==0)
{
pthread_mutex_lock(&lock);
MatrixC=map_matrix_chunk2("./MatrixC",2,i,j%(chunk_size/4));
//pthread_mutex_unlocck(&lock);
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
/*int o;
for(o=0;o<chunk_size/4;o++)
printf(" %d",MatrixC[o]);

seek=i*nRows*4+(((j+1)/(chunk_size/4))-1)*chunk_size;
printf("\n seek valeu is ......%d",seek);
printresult("./MatrixC",seek);



int a;
scanf("%d",&a);







*/
/*int fd=open("./MatrixC",O_RDWR);
if(fd==-1)
{


perror("File not opened ");
exit(1);

}*/
//seek=i*nRows*4+(((j+1)/(chunk_size/4))-1)*chunk_size;
//lseek(fd,seek,0);
int loc=0,w,buf=0;

//read(fd,&buf,4);
//printf("--rammmmmmmmmmmmmmm        %d -\n",buf);
//if(j+1==nRows)
//limit=chunk_size/4-padding;
//lse
for(loc=0;loc<chunk_size/4;loc++)
{buf=MatrixC[loc];
//printf("%d ",buf);
 w=write(fd,&buf,4);
}
munmap(MatrixC,chunk_size);

//printresult("./MatrixC",seek);

//printMatrix("./MatrixC");
//scanf("%d",&buf);
/*
int fd=open("./MatrixC",O_RDWR);
if(fd==-1)
{


perror("File not opened ");
exit(1);

}
seek=i*nRows*4+(((j+1)/(chunk_size/4))-1)*chunk_size;
lseek(fd,seek,0);


int *filec=mmap(NULL,chunk_size,PROT_WRITE|PROT_READ,MAP_SHARED,fd,0);
if(filec==(void *)-1)
{
printf("\n copy error \n");
exit(1);
}
memcpy(filec,MatrixC,chunk_size);
int o;
read(fd,&o,4);
printf("%d ++++++++",o);

for(o=0;o<chunk_size/4;o++)
printf("%d ",filec[o]);
printf("---------------\n");


munmap(filec,chunk_size);
int buf,x;
lseek(fd,seek,0);
for(x=0;x<chunk_size/4;x++)
{
read(fd,&buf,4);
printf("%d ",buf);
}
scanf("%d",&buf);
close(fd);*/
}
pthread_mutex_unlock(&lock);
}
//printMatrix("./MatrixC");
//getchar();


}
void  map_Matrix()
{

int i,j,k;
int fd=open("./MatrixC",O_RDWR);
if(fd==-1)
{


perror("File not opened ");
exit(1);

}
pthread_mutex_init(&lock,NULL);
tid=(pthread_t *)malloc(sizeof(pthread_t)*nRows);

for(i=0;i<(nRows);i++)
{
pthread_create(&tid[i],NULL,doWork,&i);
}
for(i=0;i<nRows;i++)
pthread_join(tid[i],NULL);
close(fd);
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
printf("\n We assuming array size as 8192 and Chunk Size as 4096\n");
nRows=8192;
chunk_size=4096;

}
nCols=nRows;

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
nCols=nRows+padding;


struct timeval tv_start,tv_end;
gettimeofday(&tv_start,NULL);
map_Matrix();
gettimeofday(&tv_end,NULL);
printf("\n \n time taken is  %f sec ",(double)((tv_end.tv_sec-tv_start.tv_sec)+((tv_end.tv_usec-tv_start.tv_usec)/1000000)));
printf("\n\n-----------------------------------------------------------------------------------------------\n\n");
getchar();getchar();
nCols=nCols-padding;
//printf("%d ---%d \n\n",nRows,nCols);
printMatrix("./MatrixC");
return 0;
}
