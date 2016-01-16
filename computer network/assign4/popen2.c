#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
int main()
{char readbuf[80];

while(gets(readbuf)){
printf("\n %s",readbuf);
strcpy(readbuf,"");
}
return 0;
}
