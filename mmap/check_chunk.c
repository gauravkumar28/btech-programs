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

int fA,fB,fC,chunk_size,nRows,nCols;
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
for(i=0;i<nRows;i++)
{
for(j=0;j<nCols;j++)
{
int x=2,nwrite;
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
for(i=0;i<chunk_size;i++)
{
//for(j=0;j<nCols;j++)
{

nread=fread(&val,sizeof(int),1,fp);
assert(nread==1);
printf("%d ",val);

}
//printf("\n");

}

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

int cur_position =rowindex*nRows*4+colindex*4;
printf("%d cur position\n",cur_position);
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

int cur_position =nRows*4+colindex*chunk_size;
printf("%d cur position from fun 2\n",cur_position);
int x;
scanf("%d",&x);
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
void  map_Matrix()
{

int i,j,k,index;

for(i=0;i<(nRows);i++)
{
printf(" %d \n ",i+1);
for(j=0;j<(nRows*4)/chunk_size;j++)
{
printf("\n ------------- j vale is %d\n",j);
MatrixC=map_matrix_chunk2("./MatrixC",2,i,j);
memset(MatrixC,0,chunk_size);

printMatrix("./MatrixC");
int a;
scanf("%d ",&a);
index=0;

for(k=0;k<(nRows*4/chunk_size);k++)
{


MatrixA=map_matrix_chunk2("./MatrixA",1,i,k);
MatrixB=map_matrix_chunk("./MatrixB",1,j,k);
MatrixC[index]+=chunk_by_chunk_multiply(k);
//printMatrix("./MatrixC");
//getchar();
munmap(MatrixB,chunk_size);
munmap(MatrixA,chunk_size);
}
index++;
/*if((j+1)%(chunk_size/4)==0)
{
int fd=open("./MatrixC",O_RDWR);
if(fd==-1)
{


perror("File not opened ");
exit(1);

}
lseek(fd,seek*chunk_size,0);
seek++;

/*int *filec=mmap(NULL,chunk_size,PROT_WRITE|PROT_READ,MAP_SHARED,fd,0);
memcpy(filec,MatrixC,chunk_size);
int o;
for(o=0;o<chunk_size/4;o++)
printf("%d ",filec[o]);
printf("---------------\n");


printf("%d\n",seek);
munmap(filec,chunk_size);*//*
int loc=0,w,buf=0;
read(fd,&buf,4);
printf("--rammmmmmmmmmmmmmm        %d -\n",buf);
for(loc=0;loc++;loc<chunk_size/4)
{buf=MatrixC[loc];
 w=write(fd,&buf,4);
assert(w==1);}
munmap(MatrixC,chunk_size);
close(fd);
//printMatrix("./MatrixC");
scanf("%d",&buf);*/
//}
}
//printMatrix("./MatrixC");
//getchar();
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
fillMatrix("./MatrixC");
printf("\n\n Matric C.....\n\n");
//printMatrix("./MatrixC");

map_Matrix();
printf("\n\n-----------------------------------------------------------------------------------------------\n\n");
getchar();getchar();getchar();
printMatrix("./MatrixC");
return 0;
}