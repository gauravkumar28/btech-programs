#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<db.h>
#include<fcntl.h>
//using namespace std;


DB* dbpA;
DB* dbpB;
DB* dbpC;
int ret,nRows;


void fill_Matrix(char *name)
{
int i,j;

int fd=open(name,O_CREAT|O_RDWR,0666);
if(fd==-1)
{

perror("file not opened\n");
exit(1);
}

int p;
for(j=0;j<nRows;j++)
for(i=0;i<nRows;i++)
{p=2;
write(fd,&p,sizeof(int));
}
close(fd);



}


void read_Matrix(char *name)
{
int i,j;
int fd=open(name,O_RDWR,0666);
if(fd==-1)
{
perror("file not opened----------\n");
printf("%d\n",fd);
exit(1);
}
int p;
for(j=0;j<nRows;j++)
for(i=0;i<nRows;i++)
{
read(fd,&p,sizeof(int));
//cout<<*(int*)p<<" ";
//int *a=(int*)p;
printf("%d ",p);
}
printf("\n");
close(fd);
}
void openDB(DB** dbp,char *name)
{

ret=db_create(dbp,NULL,0);
if(ret!=0)
{
fprintf(stderr,"Error initializing Database structure\n");
exit(1);
}
ret=(*dbp)->open(*dbp,NULL,name,NULL,DB_BTREE,DB_CREATE,0);
if(ret!=0)
{

fprintf(stderr,"Error in opening the DataBase\n");
exit(1);
}

}
void writeDB(DB** dbp,char *name)
{

DBT key,data;
int fd=open(name,O_RDWR,0666);
if(fd==-1)
{

perror("file not opened");
exit(1);
}

int p;
int i=0;
while(read(fd,&p,sizeof(int))!=0)
{

void *keystr=(void *)&i;
int value=p;

memset(&key,0,sizeof(DBT));
memset(&data,0,sizeof(DBT));
key.data=keystr;
key.size=sizeof(keystr)+1;
data.data=&value;
data.size=sizeof(int);
ret=(*dbp)->put(*dbp,NULL,&key,&data,0);
//printf("\n %s",keyst);
if(ret!=0)
{
(*dbp)->err(*dbp,ret,"faild inserting data");
}
i++;
}
close(fd);

}


void walkDB(DB** dbp,char* name)
{
printf("\n DATABASE %s Has \n",name);
DBC *cursorp;
DBT key,data;
(*dbp)->cursor(*dbp,NULL,&cursorp,0);
memset(&key,0,sizeof(DBT));
memset(&data,0,sizeof(DBT));

while(!(ret=cursorp->c_get(cursorp,&key,&data,DB_NEXT)))
{
//cout<<key.data<<*(int*)data.data;
printf(" %d",*(int*)data.data);
}
if(cursorp!=NULL)
cursorp->c_close(cursorp);
printf("\n");
}

void matmat_add(DB** dbpa,DB** dbpb,DB** dbpc)
{
DBC *cursorpa,*cursorpb,*cursorpc;
DBT keya,keyb,keyc,dataa,datab,datac;
(*dbpa)->cursor(*dbpa,NULL,&cursorpa,0);
memset(&keya,0,sizeof(DBT));
memset(&dataa,0,sizeof(DBT));
(*dbpb)->cursor(*dbpb,NULL,&cursorpb,0);
memset(&keyb,0,sizeof(DBT));
memset(&datab,0,sizeof(DBT));
while(!(ret=cursorpa->c_get(cursorpa,&keya,&dataa,DB_NEXT))&&!(ret=cursorpb->c_get(cursorpb,&keyb,&datab,DB_NEXT)))
{

printf(" %d",*(int*)dataa.data+*(int*)datab.data);

}




}
/*
void matmat_mul(DB** dbpa,DB** dbpb,DB** dbpc)
{
int sum=0;
DBC *cursorpa,*cursorpb,*cursorpc;
DBT keya,keyb,keyc,dataa,datab,datac;
(*dbpa)->cursor(*dbpa,NULL,&cursorpa,0);
memset(&keya,0,sizeof(DBT));
memset(&dataa,0,sizeof(DBT));
(*dbpb)->cursor(*dbpb,NULL,&cursorpb,0);
memset(&keyb,0,sizeof(DBT));
memset(&datab,0,sizeof(DBT));
while(!(ret=cursorpa->c_get(cursorpa,&keya,&dataa,DB_NEXT))&&!(ret=cursorpb->c_get(cursorpb,&keyb,&datab,DB_NEXT)))
{

sum+=(*(int*)dataa.data)*(*(int*)datab.data);

}

printf("\n the multiplication result  is...\t %d\n",sum);


}
*/


void matmat_mul(DB** dbpa,DB** dbpb,DB** dbpc)
{
void *keystra,*keystrb;
int i,j,k;
DBC *cursorpa,*cursorpb,*cursorpc;
DBT keya,keyb,keyc,dataa,datab,datac;
ret=(*dbpa)->cursor(*dbpa,NULL,&cursorpa,0);
if(ret!=0)
{

perror("ret  cusor error");
}

memset(&keya,0,sizeof(DBT));
memset(&dataa,0,sizeof(DBT));
ret=(*dbpb)->cursor(*dbpb,NULL,&cursorpb,0);
if(ret!=0)
{

perror("ret  cusor error");
}
memset(&keyb,0,sizeof(DBT));
memset(&datab,0,sizeof(DBT));

for(i=0;i<nRows;i++)
{

int b=i*nRows;
keystra=(void*)&b;
memset(&keya, 0, sizeof(keya));
	keya.data = keystra;
	keya.size = sizeof(keystra)+1;
	memset(&dataa, 0, sizeof(dataa));
ret=cursorpa->c_get(cursorpa,&keya,&dataa,DB_SET);
//printf("%d \n",*(int*)dataa.data);

for(j=0;j<nRows;j++)
{
int sum=0;
int c=j*nRows;
keystrb=(void*)&c;
memset(&keyb, 0, sizeof(keyb));
	keyb.data = keystrb;
	keyb.size = sizeof(keystrb)+1;
	memset(&datab, 0, sizeof(datab));
ret=cursorpb->c_get(cursorpb,&keyb,&datab,DB_SET);

for(k=0;k<nRows;k++)
{
ret=cursorpb->c_get(cursorpb,&keyb,&datab,DB_NEXT);
ret=cursorpa->c_get(cursorpa,&keya,&dataa,DB_NEXT);
sum+=(*(int*)dataa.data)*(*(int*)datab.data);
}
printf("%d \n",sum);
}
printf("\n shyam\n");
}
if(cursorpa!=NULL)
cursorpa->c_close(cursorpa);
if(cursorpb!=NULL)
cursorpb->c_close(cursorpb);
if(cursorpc!=NULL)
cursorpc->c_close(cursorpc);
}
void deleteDB(DB** dbp,char *name)
{

(*dbp)->remove(*dbp,name,NULL,0);
}

void closeDB(DB** dbp)
{
if(*dbp!=NULL)
(*dbp)->close(*dbp,0);
}



int main(int argc,char *argv[])
{

if(argc==1)
{
nRows=100;
//nCols=100;
}
if(argc==2)
{

nRows=atoi(argv[1]);

}
fill_Matrix("./MatrixA");
fill_Matrix("./MatrixB");
fill_Matrix("./MatrixC");
//read_Matrix("./MatrixA");
openDB(&dbpA,"MatrixA.db");

openDB(&dbpB,"MatrixB.db");
openDB(&dbpC,"MatrixC.db");
int a;


writeDB(&dbpA,"./MatrixA");
writeDB(&dbpB,"./MatrixB");
writeDB(&dbpC,"./MatrixC");
//walkDB(&dbpA,"MatrixA.db");
//walkDB(&dbpB,"MatrixB.db");
//walkDB(&dbpC,"MatrixC.db");
//matmat_add(&dbpA,&dbpB,&dbpC);
matmat_mul(&dbpA,&dbpB,&dbpC);
//closeDB(&dbpA);
//closeDB(&dbpB);
//closeDB(&dbpC);
deleteDB(&dbpA,"MatrixA.db");
deleteDB(&dbpB,"MatrixB.db");
deleteDB(&dbpC,"MatrixC.db");
unlink("./MatrixA");
unlink("./MatrixB");
unlink("./MatrixC");
return 0;
}
