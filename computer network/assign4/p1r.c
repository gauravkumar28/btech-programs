#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    char charbuf[80];
int fd[2];
pipe(fd);
int a=fork();
if(a>0)
{close(fd[0]);
dup2(fd[1],1);
execv("./p2r",NULL);
wait(NULL);
}

else
{
close(fd[1]);
bzero(charbuf,80);
read(fd[0],charbuf,80);
write(1,charbuf,80);

}
return 0;
}
