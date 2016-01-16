#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>

size_t nrows = 3000;
size_t ncols;

inline size_t
getID (int i, int j)
{
  assert (i >= 0 && i < nrows);
  assert (j >= 0 && j < ncols);

  return j * nrows + i;
}

inline float
getVal (const char *buf, int i, int j)
{
  float val;
  size_t id = getID(i, j);
  size_t offset = id * sizeof (float);
  memcpy (&val, &buf[offset], sizeof (float));
  return val;
}

inline void
setVal (char *buf, int i, int j, float val)
{
  size_t id = getID(i, j);
  size_t offset = id * sizeof (float);
  memcpy (&buf[offset], &val, sizeof (float));
}

void
fill_matrix (char *fname)
{
  FILE *fp = fopen (fname, "w+");
  if (fp == NULL)
    {
      printf (" Cann't open the file: %s \n", fname);
      return;
    }

  int counter = 1;
  int nwrite;
  for (size_t j = 0; j < ncols; j++)
    {
      for (size_t i = 0; i < nrows; i++)
	{
	  size_t id = getID (i, j);
	  float val = drand48 ();
	  nwrite = fwrite (&val, sizeof (float), 1, fp);
	  assert (nwrite == 1);
	}
    }
  fclose (fp);
}

void
print_file (const char *fname)
{
  FILE *fp = fopen (fname, "r");
  if (fp == NULL)
    {
      printf (" Cann't open the file: %s \n", fname);
      return;
    }

  float val;
  for (size_t i = 0; i < nrows; i++)
    {
      for (size_t j = 0; j < ncols; j++)
	{
	  fread (&val, sizeof (float), 1, fp);
	  printf ("%lf ", val);
	}
      printf ("\n \n");
    }
}

void
print_matrix (const char *buf)
{
  float val;
  for (size_t i = 0; i < nrows; i++)
    {
      for (size_t j = 0; j < ncols; j++)
	{
	  val = getVal (buf, i, j);
	  printf ("%lf ", val);
	}
      printf ("\n \n");
    }
}

void
print_buf (const char *buf)
{
  float val;
  for (size_t j = 0; j < ncols; j++)
    {
      printf (" Col #%d \n", j);
      for (size_t i = 0; i < nrows; i++)
	{
	  val = getVal (buf, i, j);
	  printf ("%lf \n", val);
	}
      getchar ();
    }
  printf (" Buf reading over \n");
}

void
transpose (char *buf)
{
  float vij, vji;
  for (int i = 0; i < nrows; i++)
    {
      for (int j = i; j < ncols; j++)
	{
	  vij = getVal (buf, i, j);
	  vji = getVal (buf, j, i);
	  setVal (buf, i, j, vji);
	  setVal (buf, j, i, vij);
	}
    }
}

char *
gen_rand_matrix (char *fname, int nrows, int ncols, int *fileid)
{
  int  fd, stat;
  size_t mapsize;
  char *map_addr;
  float *ma;

  ncols = nrows;
  mapsize = nrows * ncols * sizeof (float);

  fill_matrix (fname);
  printf (" Matrix Filled \n");

  fd = open (fname, O_RDWR);
  if (fd <= 0)
    {
      printf ("Error: Cann't open file matrixA \n");
      return NULL;
    }

  map_addr =
    (char *) mmap (0, mapsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (map_addr == MAP_FAILED)
    {
      printf ("Error: mmap failed \n");
      return NULL;
    }
  stat = madvise (map_addr, mapsize, MADV_RANDOM);
  if( stat ) printf( " Warning: Random IO advise not set \n");
  
  *fileid = fd;

  return map_addr;
}

void
matrix_matrix_multiply (char *mc, const char *ma, const char *mb)
{
  int i, j, k;
  float sum, aik, bkj;
  printf (" Multiplication Starts ... \n");
  for (i = 0; i < nrows; i++)
    {
      for (j = 0; j < ncols; j++)
	{
	  sum = 0.0;
	  for (k = 0; k < ncols; k++) {
            aik  = getVal(ma,i,k);
            bkj  = getVal(mb,k,j);
	    sum += aik*bkj;
          }
	  setVal(mc, i, j, sum);
	}
    }
  printf (" Multiplication Ends ... \n");
}

int
main ()
{
  int fda, fdb, fdc;
  char *ma, *mb, *mc;
  ncols = nrows;
  size_t mapsize = nrows * ncols * sizeof (float);

  ma = gen_rand_matrix ("matrixA", nrows, ncols, &fda);
  mb = gen_rand_matrix ("matrixB", nrows, ncols, &fdb);
  mc = gen_rand_matrix ("matrixC", nrows, ncols, &fdc);

  matrix_matrix_multiply (mc, ma, mb);

  munmap (ma, mapsize);
  munmap (mb, mapsize);
  munmap (mc, mapsize);

  close (fda);
  close (fdb);
  close (fdc);
}
