#include<iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
using namespace std;
string code="";
struct node
{
  int k;
 string s;
  struct node* left;
  struct node* right;
}*root=NULL;

void search(char key,node* t)
{int flag=0;
if(t->left==NULL)
return;
else if(t->right==NULL)
return;
 else  if(t->left!=NULL)
{
  for(int i=0;i<t->left->s.length();i++){
  if(key==t->left->s[i])
 {
  flag=1;break;}}
}
  if(t->right!=NULL)
 {
    for(int i=0;i<t->right->s.length();i++){
  if(key==t->right->s[i])
 {flag=2;break;}}

 }
if(flag==2)
{code=code+'1';
search(key,t->right);
}
else if(flag==1){code=code+'0';
search(key,t->left);
}


}
void inorder(node *t)
{
if(t!=NULL)
{
  inorder(t->left);
  cout<<"\n "<<t->k<<"\t"<<t->s;
  inorder(t->right);
}

}
void swap(int &x,int &y)
{
  int z;
  z=x;
  x=y;
  y=z;
  return;
}
int main()
{int a;
int key[10];
cout<<"\n enter the key ";
for(int i=0;i<10;i++)
key[i]=rand()%100;
for(int i=0;i<10;i++)
for(int j=0;j<10-1;j++)
if(key[j]>key[j+1])
swap(key[j],key[j+1]);
cout<<endl;

for(int i=0;i<10;i++)
cout<<key[i]<<"\t";
int id=97;
node* t1=new node();
t1->left=NULL;
t1->right=NULL;
t1->k=key[0];
t1->s=id;
id++;
node* t2=new node();
t2->left=NULL;
t2->right=NULL;
t2->k=key[1];
t2->s=id;
id++;
root=new node();
root->left=t1;
root->right=t2;
root->k=t1->k+t2->k;
root->s=t1->s+t2->s;
int j=2;
while(j<10)
{
int l;int sum=0;int count=0;
for(int l=j;l<10;l++)
if(sum>root->k)
break;
else
{sum=sum+key[l];count++;}
node* cur;int m;
for(m=0;m<count;m++)
{if(m==0)
{node*t=new node();
t->k=key[j++];
t->s=id++;
t->left=NULL;
t->right=NULL;
cur=t;

}
  else
  {node*t=new node();
t->k=key[j++];
t->s=id++;
t->left=NULL;
t->right=NULL;
node* ptr=new node();
ptr->left=cur;
ptr->right=t;
ptr->k=cur->k+t->k;
ptr->s=cur->s+t->s;
cur=ptr;


  }
}
if(m==count)
{
  node* temp=new node();
 temp->left=root;
 temp->right=cur;
 temp->k=root->k+cur->k;
 temp->s=root->s+cur->s;
 root=temp;
 count=0;
}
}
inorder(root);
char hfcode;
int n;
do{
cout<<"\n enter the key to  get hoffman code\t";
cin>>hfcode;
search(hfcode,root);
cout<<endl<<"hoffman code is\t";
cout<<code;
code="";
cout<<"\n press one to continue\n";
cin>>n;
}while(n==1);
return 0;
}

