#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<tbb/task_scheduler_init.h>
#include<tbb/parallel_for.h>
#include<tbb/blocked_range.h>
#include "tbb/tick_count.h"
using namespace std;
using namespace tbb;
class VectMat
{
private: double *const vectA,*const vectB,*const resultVect;
public:
VectMat(double *a,double *b,double *resultV):vectA(a),vectB(b),resultVect(resultV){}
void operator() (blocked_range<size_t>&r)const
{
double *vA,*vB,*vR;
vA=vectA;
vB=vectB;
vR=resultVect;
for(size_t count=r.begin();count!=r.end();count++)
vR[count]=vA[count]*vB[count];
}
};


int main(int argc,char*argv[])
{
double *vectA,*vectB,*resultVect;
size_t length;
if(argc!=2)
{
printf("Error in commandline <vector size>\n");exit(1);
}
length=atoi(argv[1]);
vectA=(double*)malloc(length*sizeof(double));
vectB=(double*)malloc(length*sizeof(double));
resultVect=(double*)malloc(length*sizeof(double));
for(size_t i=0;i<length;i++)
{
vectA[i]=vectB[i]=1.5;
resultVect[i]=0.0;
}

task_scheduler_init init;
tick_count t0=tick_count::now();
parallel_for(blocked_range<size_t>(0,length,1000),VectMat
(vectA,vectB,resultVect));
tick_count t1=tick_count::now();

for(int i=0;i<length;i++)
printf("%f  ",resultVect[i]);
printf("\n\t\tMultiplication Done in %f sec\n",(t1-t0).seconds());
return 0;
}
