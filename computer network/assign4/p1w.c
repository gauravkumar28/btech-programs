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

execv("./p2w",NULL);
wait(NULL);
}

else
{
close(fd[1]);
dup2(fd[0],0);
bzero(charbuf,80);
gets(charbuf);
write(0,charbuf,80);


}
return 0;
}
