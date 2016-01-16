#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{

char buf[100];
memset(buf,0,100);
printf("service man says\n");
read(0,buf,100);
write(1,buf,100);


}
