/*
SUMMER INTERNSHIP PROJECT 2013 AT CDAC HPC-FTE BY NIT WARANGAL STUDENTS
Objective: To perform matrix multiplication using mmap() with multiply operations performed in blocks in limited memory requirements

Author:Srikanth Grandhe
       B.Tech 3/4,CSE
       NIT Warangal


Input: ARGUMENT 1: ROW SIZE OF MATRIX A (ROWSA)
       ARGUMENT 2: ROW SIZE OF MATRIX B (ROWSB)
       ARGUMENT 3: COLUMN SIZE OF MATRIX B (COLS)
       Each element in the matrix is of type Integer or Float

Output: MATRIX C OF ORDER (ROWSA X COLS)
        OUTPUT STORED IN BINARY FILE matC
        EXECUTION TIME OF MULTIPLY FUNCTION

CONCEPT USED: 
1.Create 3 files with file name matA,matB and matC.
2.Matrix A is stored with random values.
3.Matrix B is stored with random values in its transpose form
4.In the multiplication function each row is split into blocks and multiplication is observed in terms of block multiplication. Based upon the RAM limitations atleast one page of memory is needed for each of the matrices. During the multiplication process the required pages are initially loaded while maintaining information about offset and page numbers in the data structure named "information".Blocks of memory are fetched from the mapped pages into the buffers and multiplication is performed while all the elements in the selected row are not accessed. 
5.To load the block buffers with the required values fetch_block_A() and fetch_block_B() are used. Different conditions are observed while l
loading values into the buffer from mapped pages-
i)If the entire block to be fetched is available in the mapped pages then access these elements and load the block buffers for the required matrix.
ii)If block to be fetched is partly available in the mapped page then load these elements into the block buffer.Once this operation is performed munmap() this page.Now map() the next page using information available in the "information" structure and load the remaining required elements into the buffer.Update the offset and page information in the "information" structure.
iii)If elements left to be accessed in the row are less than the standard block size assumed then access only the required number and load the remaining buffer with 0.  

Repeat the same operation on every row till all the elements of matrix C are computed.
             
*/

#include<stdio.h>
#include<sys/time.h>
#include<sys/mman.h>
#include<fcntl.h>
#include<stdlib.h>
#include<unistd.h>


//ram_size needs to be atleast 4 page sizes
#define PAGE_SIZE 4096*32
//block size can be any value less than page size/4
#define BLOCK_SIZE 600
//block size refers to number of elements to be read at once




void input_matrixA(char* file_name,int rows,int columns)
{
	int fd=open(file_name,O_WRONLY|O_CREAT,0666);
	int arr_size=BLOCK_SIZE/sizeof(int);
	int buf[BLOCK_SIZE/sizeof(int)]={0};
	int count=0;
	int i=0;
	
	while(count<=2*(rows*columns))
	{
		if(count>0 && count%arr_size==0)
		{
			write(fd,buf,(i)*sizeof(int));
			i=0;
		}

		buf[i]=2;
		
		count++;
		i++;
	}
	close(fd);
	printf("matrix A completed\n");
}



void input_matrixB(char* file_name,int rows,int columns)
{
	int fd=open(file_name,O_WRONLY|O_CREAT,0666);
	int arr_size=BLOCK_SIZE/sizeof(int);
	int buf[BLOCK_SIZE/sizeof(int)]={0};
	int count=0;
	int i=0;
	while(count<=2*(rows*columns))
	{
	//directly storing the matrix in its transpose form
		if(count>0 && count%arr_size==0)
		{
			write(fd,buf,(i)*sizeof(int));
			i=0;
		}

		buf[i]=3;
	
		count++;
		i++;
	}
	close(fd);
	printf("matrix B completed\n");
}

//data structure maintaining information required while loading elements into buffers from mapped pages
struct information
{
	int current_offset_A;
	int page_num_A;
	int current_offset_B;
	int page_num_B;
	int elements_left_A;
}info;


int *mat_a_ptr,*mat_b_ptr,*mat_c_ptr;
int fda,fdb,fdc;


void fetch_block_A(int* temp_arr)
{
	if(info.current_offset_A==0 && info.page_num_A==0)
	mat_a_ptr=(int*)mmap(NULL,PAGE_SIZE,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_FILE,fda,0);
	//if block not accessing the last element in the page
	if(info.current_offset_A+BLOCK_SIZE*4<PAGE_SIZE)
	{
		int i;
		for(i=0;i<BLOCK_SIZE;i++)
		*(temp_arr+i)=*(mat_a_ptr+i+(info.current_offset_A)/4);
		info.current_offset_A+=BLOCK_SIZE*4;
		return;
	}
	else
	{
	//if accessing last element of the required page
		int can_access=(PAGE_SIZE-info.current_offset_A)/4;
		int i;
		for(i=0;i<can_access;i++)
		*(temp_arr+i)=*(mat_a_ptr+i+(info.current_offset_A)/4);
	
	//block is filled incompletely and more elements need to be filled from next page
		int needed=BLOCK_SIZE-can_access;
		munmap(mat_a_ptr,PAGE_SIZE);
		info.page_num_A++;
		mat_a_ptr=(int*)mmap(NULL,PAGE_SIZE,PROT_READ|PROT_WRITE,MAP_PRIVATE,fda,(info.page_num_A)*PAGE_SIZE);
		for(i=0;i<needed;i++)
		*(temp_arr+i)=*(mat_a_ptr+i);
		info.current_offset_A=needed*4;
		return;
	}
}



void fetch_block_B(int* temp_arr,int size)
{

	if(info.current_offset_B==0 && info.page_num_B==0)
	mat_b_ptr=(int*)mmap(NULL,PAGE_SIZE,PROT_READ|PROT_WRITE,MAP_PRIVATE,fdb,0);

	if((info.current_offset_B+(size*4))<=PAGE_SIZE)
	{
		int i;
		for(i=0;i<size;i++)
		*(temp_arr+i)=*(mat_b_ptr+i+(info.current_offset_B)/4);
		info.current_offset_B+=size*4;
		return;
	}
	else
	{
		int can_access=(PAGE_SIZE-info.current_offset_B)/4;
		int i;
		for(i=0;i<can_access;i++)
		*(temp_arr+i)=*(mat_b_ptr+i+(info.current_offset_B)/4);
		int needed=BLOCK_SIZE-can_access;
		munmap(mat_b_ptr,PAGE_SIZE);
		info.page_num_B++;
		mat_b_ptr=(int*)mmap(NULL,PAGE_SIZE,PROT_READ|PROT_WRITE,MAP_PRIVATE,fdb,(info.page_num_B)*PAGE_SIZE);
		for(i=0;i<needed;i++)
		*(temp_arr+i)=*(mat_b_ptr+i);
		info.current_offset_B=needed*4;
		return;
	}
}





void matrix_multiplication(int rows_mat_a,int rows_mat_b,int columns_mat_b)
{
	
	int count=1;
	mat_a_ptr=mat_b_ptr=NULL;
	//initialisation of information variables
	info.current_offset_A=0;
	info.page_num_A=0;
	info.page_num_B=0;
	info.current_offset_B=0;
	//file processing implemented in the fetch methods itself
	fda=open("matrixA",O_RDONLY,0666);
	fdb=open("matrixB",O_RDONLY,0666);
	fdc=open("matrixC",O_WRONLY,0666);
	
	int bufC[PAGE_SIZE/sizeof(int)]={0};
	int x=0;
	int i,j,k,y;
	for(i=0;i<rows_mat_a;i++)
	{
		info.current_offset_B=0;
		info.page_num_B=0;
		int temp_offset=info.current_offset_A;
		int temp_page=info.page_num_A;
		if(mat_b_ptr)
		munmap(mat_b_ptr,PAGE_SIZE);
	
		for(j=0;j<columns_mat_b;j++)
		{
	
			int temp=0;//variable to store temporary result of the block
			info.elements_left_A=rows_mat_b;
				
			for(y=0;y<=rows_mat_b/BLOCK_SIZE;y++)
			{
				int arr1[BLOCK_SIZE]={0};
				fetch_block_A(arr1);
				//printf("read block from A\n");
				info.elements_left_A-=BLOCK_SIZE;
				int arr2[BLOCK_SIZE]={0};
				//checking the number of elements to be filled in the block before accessing from the page for maintaining correct offset information for further use
				int size=info.elements_left_A<0?info.elements_left_A+BLOCK_SIZE:BLOCK_SIZE;
				fetch_block_B(arr2,size);


				//performing multiplication of the blocks and adding to temp variable to collect final result
				for(k=0;k<size;k++)
				temp+=arr1[k]*arr2[k];
			}

			//modify offset values here.......resetting offset to compute next element 
			if(j<columns_mat_b-1)
			{
				info.current_offset_A=temp_offset;
				if(info.page_num_A!=temp_page)
				{
					info.page_num_A=temp_page;
					munmap(mat_a_ptr,PAGE_SIZE);
					mat_a_ptr=(int*)mmap(NULL,PAGE_SIZE,PROT_READ|PROT_WRITE,MAP_PRIVATE,fda,(info.page_num_A)*PAGE_SIZE);
				}
			}

			//storing result for one element in matC in the buffer

			bufC[x++]=temp;
			//later store this value in file directly
			if(x==PAGE_SIZE/sizeof(int))
			{
				write(fdc,bufC,sizeof(int)*x);
				x=0;
			}
		}
		printf("%d\n",count);
		count++;

	}

	if(mat_a_ptr)
	munmap(mat_a_ptr,PAGE_SIZE);
	if(mat_b_ptr)
	munmap(mat_b_ptr,PAGE_SIZE);
	write(fdc,bufC,sizeof(int)*x);
	close(fda);
	close(fdb);
	close(fdc);
}



int main(int argc,char* argv[])
{
	//order of matrix1 is argv[1]xargv[2]
	//order of matrix2 is argv[2]xargv[3] 
	int rows_mat_a=atoi(argv[1]);
	int rows_mat_b=atoi(argv[2]);
	int columns_mat_b=atoi(argv[3]);

	input_matrixA("matrixA",rows_mat_a,rows_mat_b);
	input_matrixB("matrixB",rows_mat_b,columns_mat_b);
	input_matrixA("matrixC",rows_mat_a,columns_mat_b);

	printf("ready for multiplication\n");
	struct timeval t1;
	gettimeofday(&t1,NULL);
	
	printf("going to multiply\n");
	matrix_multiplication(rows_mat_a,rows_mat_b,columns_mat_b);
	printf("multiplication completed\n");

	struct timeval t2;
	gettimeofday(&t2,NULL);
	if(t2.tv_usec<t1.tv_usec)
	{
		//printf("time manipuation\n");
		t2.tv_sec-=1;
		t2.tv_usec=1000000+t2.tv_usec;
	}


		//display of matrix C
		/*
	fdc=open("matC",O_RDONLY,0666);
	int x,y,s;
	for(x=0;x<rowsa;x++)
	{
	for(y=0;y<cols;y++)
	{
	read(fdc,&s,sizeof(int));
	printf("%d ",s);
	}
	printf("\n");
	}
	close(fdc);
	*/

	printf("time taken=%ld.%.6ldsec\n",(long)(t2.tv_sec-t1.tv_sec),(long)(t2.tv_usec-t1.tv_usec));
	return 0;
}
