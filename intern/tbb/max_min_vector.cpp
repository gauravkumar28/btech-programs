#include<stdio.h>
#include<iostream>
#include<tbb/task_scheduler_init.h>
#include<tbb/parallel_reduce.h>
#include<tbb/blocked_range.h>
#include<float.h>
#include<sched.h>
#include<sys/time.h>
#include<stdlib.h>
#include<errno.h>
using namespace std;
using namespace tbb;
class MinMaxCal
{
private: const float *const ArrayA;
public: float MinValue;
long IndexMinVal;
float MaxValue;
long IndexMaxVal;
void operator() (const blocked_range<size_t>&r)
{
const float* a=ArrayA;
float val;
for(size_t i=r.begin();i!=r.end();++i)
{
val=a[i];
if(val<MinValue)
{
MinValue=a[i];
IndexMinVal=i;
}
if(val>MaxValue)
{
MaxValue=val;
IndexMaxVal=i;
}
}
}

MinMaxCal(MinMaxCal &x,split):ArrayA(x.ArrayA),MinValue(FLT_MAX),MaxValue(-FLT_MAX),IndexMinVal(-1),IndexMaxVal(-1) {}
void join(const MinMaxCal &y)
{
if(y.MinValue<MinValue)
{
MinValue=y.MinValue;
IndexMinVal=y.IndexMinVal;
}
if(y.MaxValue>MaxValue)
{
MaxValue=y.MaxValue;
IndexMaxVal=y.IndexMaxVal;
}
}
MinMaxCal(const float *A):
ArrayA(A),MinValue(FLT_MAX),
IndexMinVal(-1), 
MaxValue(-FLT_MAX),
IndexMaxVal(-1)
{}
};
int main(int argc,char *argv[])
{
int rc;
int seed;
struct timeval tv_start,tv_end;
struct timezone tz_start,tz_end;
long timetaken;
unsigned long ThreadAffMask;
unsigned int ThreadAffMaskLen=sizeof(ThreadAffMask);
pid_t ProgPid=getpid();

float *Array;
long ArraySize;
size_t GrainSize;
if(argc==4)
{
ArraySize=atoi(argv[1]);
GrainSize=atoi(argv[2]);
if(atoi(argv[3])>0)
ThreadAffMask=atoi(argv[3]);
rc=sched_setaffinity(ProgPid,ThreadAffMaskLen,(cpu_set_t *)&ThreadAffMask);
if(rc==-1)
cout<<"Couldn't set thread affinity\n";
}
else if(argc==3)
{
ArraySize=atoi(argv[1]);

GrainSize=atoi(argv[2]);
}
else if(argc==2)
{
cout<<"usage : "<< argv[0] <<" <ArraySize> <GrainSize>\n assuming GrainSize 1000";
ArraySize=atoi(argv[1]);
GrainSize=1000;
}
else
{
cout<<"Usage : "<<argv[0] << "<ArraySize> <GrainSize> <ThreadAffMask>\n" "assuming ArraySize =1000\n"
"Grain size =1000\n";
ArraySize=1000;
GrainSize=10000;
}
if(ArraySize>0)
Array=new float[ArraySize];
else
perror("Value of Array Size should be +ve");
for(int i=0;i<ArraySize;i++)
{
seed=i;
Array[i]=(rand_r((unsigned int *)&seed)%2000)+1.5;
}
task_scheduler_init init;
MinMaxCal MMC(Array);
gettimeofday(&tv_start,&tz_start);
parallel_reduce(blocked_range<size_t>(0,ArraySize,GrainSize),MMC);
gettimeofday(&tv_end,&tz_end);
timetaken=tv_end.tv_sec*1000000+tv_end.tv_usec-tv_start.tv_sec*1000000-tv_end.tv_usec;
if(argc==4)
{
rc=sched_getaffinity(ProgPid,ThreadAffMaskLen,(cpu_set_t *)&ThreadAffMask);
printf(" pid %d's executed with affinity %08lx \n\n",ProgPid,ThreadAffMask);
}

cout<<"Minimum value of the vector ="<<MMC.MinValue<<"at index "<<MMC.IndexMinVal;
cout<<"Maximum value of the Vector ="<<MMC.MaxValue<<" at index "<<MMC.IndexMaxVal;
cout<<"Time Taken in sec   "<<timetaken/1000000;

return 0;
}
