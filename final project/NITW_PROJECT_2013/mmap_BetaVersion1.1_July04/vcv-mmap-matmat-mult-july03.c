/*
*PROJECT Name : Application of MMAP And OPENMP  
*
* AUTHER : GAURAV KUMAR
*
* DATE: 1/07/2013
*
* INPUT: Rows_Size,Chunk_Size, BlockofRow
*
* Output: Resultant Matrix , Gigaflops and Elapsed Time in sec
*
* Limitation: Working For Matrix of size being Power of 2
*
* ******************************************************************************************************************************/

#include "mmap.h"
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/time.h>
#include<sys/stat.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<malloc.h>
#include<assert.h>
#include<omp.h>
#include<math.h>
#include <mkl.h>


#define EPS 1.0e-12 /* threshhold aprrox epsilion value */ 
			//#define block_of_row 256


double alpha = 1.0, beta = 0.0;
float  *elapsedTime; /* holds total elapsed time */
double Gflops; /* holds FLOPS */
double Tsec_cpu=0.0,Tsec_gpu=0.0; /* holds time taken for computation on CPU */
/* struct timeval tv_start, tv_end;  */
/* variable to hold start / end time for CPU*/

double time_start, time_end;
       struct timeval tv;
       struct timeval tz;

int Chunk_Size,Total_Row,Total_Col,Padding,Block_Of_Row,Total_Thread;

int seek=0;

double *MatrixA,*MatrixB,*MatrixC;
double *bufferA,*bufferB,*bufferC;

/* ................................................................... */
double nrmsdError(int Rows_Size, int Columns_Size, \
                           double (*  M1), \
                           double (*  M2))
{

 	 double sum = 0.0;
 	 double max, min;
 	 max =min= (M1[0]- M2[0]);

 	 int i,j;
	double diff;
  	#pragma omp  parallel for private(i,j,diff,min,max) reduction(+:sum)
  	for ( i = 0; i < Rows_Size; ++i){
  	for ( j = 0; j < Rows_Size;++j) {
     	diff = (M1[i*Rows_Size+j]- M2[i*Rows_Size+j]);
    	#pragma omp critical     
    	  {
        max = (max > diff)?max:diff;
        min = (min < diff)?min:diff;
        sum += diff*diff;
    	  }
    	}
	}
    
    return(sqrt(sum/(Rows_Size*Rows_Size)));
}

/* ................................................................... */

double doCheck(int Rows_Size, int Columns_Size, \
                  double (*  Matrix_A), \
                  double (* Matrix_B), \
                  double (*  Matrix_C), \
                  int   nIter,  double *error)
{
 
        //  double(*restrict Cgemm)[Rows_Size] = malloc(sizeof(double)*Rows_Size*Rows_Size);
		double(* Cgemm)=(double*)malloc(Rows_Size*Rows_Size*sizeof(double));
		
          	double mklStartTime = dsecnd();

          	for(int i=0; i < nIter; i++)
              	cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, \
                    Rows_Size, Rows_Size, Columns_Size, alpha, \
                Matrix_A,Columns_Size, \
                Matrix_B, Rows_Size, beta, \
                Cgemm, Rows_Size);
         	double mklEndTime = dsecnd();

	        *error = nrmsdError(Rows_Size, Columns_Size,Matrix_C,Cgemm);
	
         	free(Cgemm);

        return (2e-9*Rows_Size*Columns_Size*Rows_Size/((mklEndTime-mklStartTime)/nIter) );
}
/* ................................................................... */


void domult(int Block_RowIndex,int Block_ColIndex)
{
        int i,j,k;
        float omp_tv_start, omp_tv_end;

        int nThreads ;
        int nIter =1;
        int Rows_Size = Block_Of_Row;
        int Columns_Size = Total_Row;

        /* .....Declared Global Variables block_of_row and nRows  ... */
        /* MATRIX A OF SIZE "block_of_row X nRows" is multiplied with 
           MATRIX B OF SIZE "nRows X block_of_row"  */

        omp_tv_start = omp_get_wtime();
        printf("\nbufferA having index %d\t bufferB having index %d\n ", \
                 Block_RowIndex/Block_Of_Row,Block_ColIndex/Block_Of_Row);

        double aveTime, minTime = 1e6, maxTime =0.0;
        for (int i=0; i < nIter; i++) {
        double startTime = dsecnd();

        nThreads =Total_Thread;
        omp_set_num_threads(nThreads);

          /* .........OpenMP  implementaiton  ......*/
          /* ... Modified by vcvr  June 29-2013  ...*/
          #pragma omp parallel default (none) \
                      shared (bufferA, bufferB, bufferC, Rows_Size, Columns_Size) \
                      private(i, j, k) \

          #pragma omp for schedule(static)
          for(i=0; i<Rows_Size; i++)
          {
         //    printf(" Thread %d executes Outer loop iteration %d \n", \
                  omp_get_thread_num(), i);

            for(j=0; j<Rows_Size ; j++)
            {
             bufferC[i*Rows_Size+j] = 0.0;
              for(k = 0; k< Columns_Size ; k++)
                bufferC[i*Rows_Size + j]  += \
                (bufferA[i*Rows_Size + k])* (bufferB[j*Rows_Size + k]);
           }
          } /* --- End of omp parallel for --- */

        double endTime = dsecnd();
        double runtime = endTime - startTime;

        maxTime = (maxTime > runtime)? maxTime:runtime;
        minTime = (minTime < runtime)? minTime:runtime;

        aveTime += runtime;
     }  /* .... Average Gflops routine .... */
    aveTime /= nIter;

    omp_tv_end = omp_get_wtime();
    printf("\n\t\t Time taken ( do Mult)    :  %lf sec", (omp_tv_end - omp_tv_start));

    /* ...........Verfication of Matrix-Matrix Multiplication results ............*/
    #pragma omp parallel 
    #pragma omp master  
    printf("nThreads : %d    ITR : %d", omp_get_num_threads(), nIter);

   #pragma omp barrier   

    // do check   
    double error = 0.f;

  double mklGflop = doCheck(Rows_Size, Columns_Size,\
                             bufferA,bufferB,bufferC, nIter,&error);  
    printf("  mklGflop : %g Root_Mean_Error: %g ", mklGflop,error);    


    printf("\n");

    printf(" nThrds %d matrix Rows-A %d matrix Columns-A %d matrix Rows-B %d matrix Columns-B %d \ 
             maxRT %g minRT %g aveRT %g  ave_GFlop/s % g\n",  \
             omp_get_num_threads(), Rows_Size, Columns_Size, Columns_Size, Rows_Size, \
             maxTime, minTime, aveTime, 2e-9*Rows_Size*Columns_Size*Rows_Size/aveTime);



}



//  input matrix......................
void Fill_MMAP_Matrix(char *name)
{
        FILE *fp=fopen(name,"w+");
        if(fp==NULL)
        {

                perror("Error in opening file");
                exit(1);
        }
        int i,j;

        printf(" \n padding is %d\n",Padding);
        for(i=0;i<Total_Row;i++)
        {
                for(j=0;j<Total_Col;j++)
                {      
                        double d=2.0;
                        int nwrite=fwrite(&d,sizeof(double),1,fp);
                        assert(nwrite==1);

                }

                for(j=0;j<Padding;j++)
                {
                        double d=0.0;
                        int  nwrite=fwrite(&d,sizeof(double),1,fp);
                        assert(nwrite==1);



                }
        }
fclose(fp);
}




//printing matrix...............

void Print_MMAP_Matrix(char *name)
{
        FILE *fp=fopen(name,"r");
        if(fp==NULL)
        {
                perror("Error in Opening File");
                exit(1);
        }
        int i,j,nread;
        double val;
        for(i=0;i<Total_Row;i++)
        {
                for(j=0;j<Total_Col;j++)
                {

                        nread=fread(&val,sizeof(double),1,fp);
                        assert(nread==1);
                        printf("%lf ",val);

                }
                for(j=0;j<Padding;j++)
                {

                        nread=fread(&val,sizeof(double),1,fp);
                        assert(nread==1);
                     //   printf("%lf ",val);
                }

                printf("\n");
        }

        fclose(fp);
}


//mapping  chunk to memory


double* Map_FILE_To_Memory(char * name,int mode,int RowIndex,int ColIndex)
{
        int fd;
        if(mode==1)
                fd=open(name,O_RDONLY);
        else if(mode==2)
                fd=open(name,O_RDWR,0666);

        if(fd==-1)
        {

                perror("File not Opened  ");
                exit(1);
        }
        int cur_position =RowIndex*Total_Col*sizeof(double)+ColIndex*Chunk_Size*sizeof(double);
        lseek(fd,cur_position,SEEK_SET);
        double *map_addr=NULL;
        if(mode==1)
                map_addr=mmap(NULL,Chunk_Size*sizeof(double),PROT_READ,MAP_SHARED,fd,0);
        else if(mode==2)
                map_addr=mmap(NULL,Chunk_Size*sizeof(double),PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);


        if(map_addr==MAP_FAILED)
        {
                perror("MMAP Error");exit(1);
        }
        close(fd);

        return map_addr;

}
void  Map_And_Multiply()
{
        int Row,Col,k,Index,Block_Index;
        int fd=open("./MatrixC",O_RDWR);
        if(fd==-1)
        {
                perror("File not opened ");
                exit(1);

        }

        bufferA=(double*)malloc(sizeof(double)*Block_Of_Row*Total_Row);
        bufferB=(double*)malloc(sizeof(double)*Block_Of_Row*Total_Col);
        bufferC=(double*)malloc(sizeof(double)*Block_Of_Row*Block_Of_Row);

        for(Row=0;Row<Total_Row;Row=Row+Block_Of_Row)
        {

                for(Col=0;Col<Total_Col;Col=Col+Block_Of_Row)
                {

                        int indexA=0,indexB=0;
                        for(Block_Index=0;Block_Index<Block_Of_Row;Block_Index++)
                        {
                                for(k=0;k<(Total_Col/Chunk_Size);k++)
                                {

                                        MatrixA=Map_FILE_To_Memory("./MatrixA",1,Row+Block_Index,k);
                                        MatrixB=Map_FILE_To_Memory("./MatrixB",1,Col+Block_Index,k);
				#pragma omp parallel for shared(bufferA,bufferB,MatrixA,MatrixB) private(Index)
                                        for(Index=0;Index<Chunk_Size;Index++)
                                        {
                                             
						bufferA[indexA+Index]=MatrixA[Index];
                                                bufferB[indexB+Index]=MatrixB[Index];

                                        }

                                        munmap(MatrixB,Chunk_Size*sizeof(double));
                                        munmap(MatrixA,Chunk_Size*sizeof(double));
					indexA+=Chunk_Size;
					indexB+=Chunk_Size;
                                 }
                        }
 domult(Row,Col);
                        int p,q;
                        double Buf;
                        for(p=0;p<Block_Of_Row;p++)
                        {
                                lseek(fd,(Row+p)*Total_Row*sizeof(double)+(Col*sizeof(double)),SEEK_SET);
                                for(q=0;q<Block_Of_Row;q++)
                                {
                                        Buf=bufferC[p*Block_Of_Row+q];
                                        write(fd,&Buf,sizeof(double));

                                }
                        }
                }
        }

        close(fd);
}



void Set_Padding()
{


 Padding=Total_Row%Chunk_Size;//if nRows not power of 2
        if(Padding!=0)
                Padding=Chunk_Size-Padding;


}



int main(int argc,char **argv)
{
        if(argc==5)
        {
                Total_Row=atoi(argv[1]);
                Chunk_Size=atoi(argv[2]);
             Block_Of_Row=atoi(argv[3]);
                Total_Thread=atoi(argv[4]);
        }

        else if(argc==4)
        {
                Total_Row=atoi(argv[1]);
                Chunk_Size=atoi(argv[2]);
                Block_Of_Row=atoi(argv[3]);
                printf("\nWe assume Total_Thread as 4\n");
                Total_Thread=4;
        }

        else if(argc==3)
        {       Total_Row=atoi(argv[1]);
                Chunk_Size=atoi(argv[2]);
                printf("\n We assume Block_Of_Row as 16 and Total_Thread as 4\n");
                Block_Of_Row=16;
                Total_Thread=4;

        }

        else if(argc==1)
        {       printf("\n We assume  Total_Row 256 Chunk_Size 256 And Block_Of_Row as 16 and Total_Thread as 2\n");
                Total_Row=256;
                Chunk_Size=256;
                Block_Of_Row=16;
                Total_Thread=2;
        }



        Set_Padding();
	Total_Col=Total_Row+Padding;//appending 0's when rwo is not multiple of page size

        Fill_MMAP_Matrix("./MatrixA");

        Fill_MMAP_Matrix("./MatrixB");

        Fill_MMAP_Matrix("./MatrixC");

        gettimeofday(&tv, &tz);
        time_start = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;


        Map_And_Multiply();


/*      gettimeofday(&tv_end1,NULL); */

        gettimeofday(&tv, &tz);
        time_end = (double)tv.tv_sec + (double)tv.tv_usec / 1000000.0;

        printf("\n\t\t Computation Of Matrix A and Matrix B Computation is Done\n");
 printf("\n\t\t Time in Seconds (T)         :  %lf", time_end - time_start);
        printf("\n\t\t............................................................\n");
//	Print_MMAP_Matrix("./MatrixC");

        Total_Col=Total_Col-Padding;
        Padding = 0;

        free(bufferA);
        free(bufferB);
        free(bufferC);
        unlink("./MatrixA");
        unlink("./MatrixB");
        unlink("./MatrixC");
        return 0;
}
