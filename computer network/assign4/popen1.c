#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>

int main()
{char readbuf[80];

FILE *fp1,*fp2;
fp1=popen("./pcheck","r");
fp2=popen("./popen2","w");
 while(fgets(readbuf, 80, fp1)){
 fputs(readbuf,fp2);}
 fputs("sita",fp2);

 //printf("%s\n",readbuf);



pclose(fp1);
pclose(fp2);
return 0;
}
