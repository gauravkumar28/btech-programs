#include<iostream>
#include<string.h>
#include<math.h>
#include<stdlib.h>
using namespace std;

int main()
{int ch;
int itimer=0;
char hamming[100];
int m,r;
string msg;
do{
cout<<"\n enter the massege to send\t";
cin>>msg;
m=msg.length();
cout<<"\n msg is\t"<<msg<<"\twith length\t"<<m;
cout<<endl;
abc:
cout<<" length of redancy bit\t";
cin>>r;
if(pow(2.0,r)<(m+r+1)){
cout<<"\n this length is wrong take more length\n";
goto abc;}
int j=0;
hamming[0]='#';
int p=0;
for(int i=1;i<m+r+1;i++)
if(pow(2,p)==i){
p++;
hamming[i]='0';
}
else{
hamming[i]=msg[j];
msg[j++];
}
for(int i=0;i<r;i++)
{int parity=0;
  for(int k=pow(2,i);k<m+r+1;k=k+pow(2,i+1)){
 for(int l=0;l<pow(2,i);l++){
 if((k+l)!=pow(2,i)){
if(hamming[k+l]=='1')
parity++;}
 }
}
  if(parity%2==1)
  hamming[int(pow(2,i))]='1';

  else hamming[int(pow(2,i))]='0';
}

cout<<"\n msg to be send\t";
for(int i=1;i<m+r+1;i++)
cout<<hamming[i];
int error=0;
int errorcheck=rand()%(r+m)+1;
hamming[errorcheck]='1';
for(int i=0;i<r;i++)
{int parity=0;
  for(int k=pow(2,i);k<m+r+1;k=k+pow(2,i+1)){
 for(int l=0;l<pow(2,i);l++){
 if((k+l)!=pow(2,i)){
if(hamming[k+l]=='1')
parity++;}
 }
}
  parity=parity%2;
  if(hamming[int(pow(2,i))]!=(parity+48))
error=error+pow(2,i);
}

if(error!=0){
cout<<"\n msg get changed at \t"<<error<<endl;
}
else
cout<<"\n we recieved correct massege\n";
for(int i=1;i<m+r+1;i++)
cout<<hamming[i];

cout<<"\n if want to send more message  press 1";
cin>>ch;
}while(ch==1);
return 0;
}

