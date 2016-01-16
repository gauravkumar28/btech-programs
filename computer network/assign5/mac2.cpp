#include<iostream>
#include<stdio.h>
#include<fstream>
#include<string.h>
using namespace std;
int main()
{char s[100];
string macro[10]={""};
string macrodetail[10]={""};
char macroargument[10];
int i=0;int a=0;int d=0;
int x;
ifstream fin;
fin.open("input.cpp");
ofstream fout;
fout.open("output.cpp");
int flag10=0,flag11=0,flag=0,flag2=0;
while(!fin.eof())
{fin.getline(s,100);
char *p=strtok(s," ");
while(p!=NULL){
if(strcmp(p,"#define")==0)
{p=strtok(NULL," ");flag10=1;continue;
}
int j;
if(flag10==1)
{
for(j=0;j<strlen(p);j++){
if(p[j]=='(')
break;
else macro[i]=macro[i]+p[j];
}
i++;
for(j;j<strlen(p);j++)
if(p[j]!='('&&p[j]!=','&&p[j]!=')')
macroargument[a++]=p[j];
p=strtok(NULL," ");flag10=0;flag11=1;continue;
}
if(flag11==1)
{
for(int k=1;k<strlen(p)-1;k++)
macrodetail[d]=macrodetail[d]+p[k];
d++;
for(int m=0;m<a;m++)
{
int x;
for(x=0;x<macrodetail[d-1].length();x++)
if(macrodetail[d-1][x]==macroargument[m])
 {
char ch=m+48;
string s2="#";
s2=s2+ch;
  macrodetail[d-1].replace(x,1,s2);
  }
}
p=strtok(NULL," ");a=0;continue;
}
if(strcmp(p,"main()")==0)
{flag=1;fout<<p;p=strtok(NULL," ");continue;
}

if(flag==1)
{
  for(int k=0;k<i;k++)
 {
 char z[100];
 memset(z,0,100);
 for(int i=0;i<macro[k].length();i++)
 z[i]=macro[k][i];
 char *f;
   if((f=strstr(p,z))!=NULL)
 {char *c=p;
 while(c!=f)
 {fout<<*c;c++;}
   int q=0;int a;
   for(a=0;a<strlen(p);a++)
   if(p[a]=='(')
   break;
   for(int j=a;j<strlen(p);j++)
if(p[j]!='('&&p[j]!=','&&p[j]!=')')
macroargument[q++]=p[j];
string s3=macrodetail[k];
for(int y=0;y<q;y++)
for(int x=0;x<s3.length();x++)
if(s3[x]=='#'&&s3[x+1]==(y+48))
 {
string s2="";
s2=s2+macroargument[y];
  s3.replace(x,2,s2);
  }
  fout<<s3;

flag2=1;
 }}
}
if(flag2==0)
fout<<p<<" ";
flag2=0;
p=strtok(NULL," ");
}if(flag11==0)
fout<<endl;flag11=0;}
fin.close();
return 0;
}
