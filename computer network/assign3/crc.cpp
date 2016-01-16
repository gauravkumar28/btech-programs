#include<iostream>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
using namespace std;
int main()

{
int degree;
char gen_poly[10];
cout<<"\n enter the degree of generating polynomial\t";
cin>>degree;
string s;
bzero(gen_poly,10);
//cout<<"enter the generating polinomial\t";
for(int i=0;i<degree+1;i++)
gen_poly[i]=(rand()%2)+'0';
cout<<gen_poly;

do{
cout<<"\n enter the input code to send\t";
cin>>s;
for(int i=0;i<degree;i++)
s=s+'0';
string temp="";
for(int i=0;i<degree+1;i++)
temp=temp+s[i];
int k=degree+1;
int o=0;
string temp2="";
while(1)
{temp2="";
for(int i=0;i<degree+1;i++)
{int z=(temp[i]-48)^(gen_poly[i]-48);
char ch=z+48;
temp2=temp2+ch;
}
int m;temp="";
for(m=0;m<temp2.length();m++)
if(temp2[m]=='1')
break;
temp="";
for(int n=m;n<temp2.length();n++)
temp=temp+temp2[n];
for(int i=0;i<m;i++)
temp=temp+s[k++];
if(k>s.length())
break;
}
int i;

printf("\n msg to send is\t");
cout<<s<<endl;
s[rand()%(s.length()-degree)]=rand()%2+'0';
cout<<s;
cout<<endl;
for(i=0;i<4;i++)
s[(s.length()-1-i)]=temp2[temp2.length()-1-i];
temp="";
for(int i=0;i<degree+1;i++)
temp=temp+s[i];
k=degree+1;
o=0;
cout<<endl;
temp2="";
while(1)
{temp2="";
for(int i=0;i<degree+1;i++)
{int z=(temp[i]-48)^(gen_poly[i]-48);
char ch=z+48;
temp2=temp2+ch;
}
int m;temp="";
for(m=0;m<temp2.length();m++)
if(temp2[m]=='1')
break;
temp="";
for(int n=m;n<temp2.length();n++)
temp=temp+temp2[n];
for(int i=0;i<m;i++)
temp=temp+s[k++];
if(k>s.length())
break;
}
for(i=0;i<4;i++)
if(temp2[temp2.length()-1-i]=='1')
break;
if(i==4)
printf("\n correct meg");
else printf("\n wrong msg");
}
while(rand()%5);
return 0;
}
