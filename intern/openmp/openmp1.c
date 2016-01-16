
//print unique number for each thread started by the #pragma parallel

// output: each thread print it's id











#include<stdio.h>
#include<stdlib.h>
#include<omp.h>
int main(int argc,char **argv)
{
int threadid;
#pragma omp parallel private(threadid)
{
threadid=omp_get_thread_num();
printf("\n\t\t My thread id is : %d\n",threadid);
}
printf("\n \t\t Master thread prints this after the end parallel region \n\n");
return 0;
}
