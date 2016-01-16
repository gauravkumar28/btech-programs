#include<stdio.h>
#include<fcntl.h>

void fun()
{

int fd=open("./abc",O_RDWR);
perror("/n ++");
close(fd);
}

int main()
{
int fd=open("./abc",O_CREAT);
perror("/n hi");
close(fd);
fun();
}
