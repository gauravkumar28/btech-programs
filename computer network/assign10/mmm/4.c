#include<stdio.h>
#include<string.h>
int main()
{
	int m;
	char buf[100]="";
	m=read(100,buf,20);
	buf[m]='\0';
	//scanf("%d",&m);
	m=atoi(buf);
	sprintf(buf,"%d",m*4);
	write(100,buf,strlen(buf));
	//printf("%d\n",m*4);
	return 0;
}
