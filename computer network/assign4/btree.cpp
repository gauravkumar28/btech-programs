#include<iostream>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<cstring>
#include<stdlib.h>
#include<stdio.h>
using namespace std;
int temp[5];
int median=0;
int flag=0;
int k;
void *curr,*end_level;
struct bnode
{int key[4];
struct bnode *link[5];
};
struct qnode
{struct bnode* q;
  qnode* next;
};
class btree
{
private:
struct bnode *root;
struct qnode *head;
public:
btree();
~btree();
bool notleafnode(bnode* t);
bool overflow(bnode* t);
void print(bnode* t);
void split(bnode*t);
void sort_median(bnode*t ,int median);
void insert(bnode *&t,int k);
void inqueue(bnode* t);
bool queuenotempty();
void insertintobtree(int a);
void printlevelorder();
void splitnonleaf(bnode* t);
bnode* dqueue();
};
void sort()
{
  for(int i=0;i<5;i++)
  {
    for(int j=i;j<5;j++)
    if(temp[i]>temp[j])
    swap(temp[i],temp[j]);
    }
  median=temp[2];

}
btree::btree()
{head=NULL;
root=new bnode;
  root->key[0]=root->key[1]=root->key[2]=root->key[3]=0;
  root->link[0]= root->link[1]= root->link[2]= root->link[3]= root->link[4]=NULL;
}
bool btree::notleafnode(bnode* t)
{int a=0;
  for(int i=0;i<5;i++){
  if(t->link[i]!=NULL)
  a++;}
  if(a>0)
  return true;
  else
 return false;

}
bool btree:: overflow(bnode* t)
{int i;
  for(i=0;i<4;i++)
  if((t->key[i])==0)
  return false;
return true;
}
void btree::insert(bnode*&t,int k)
{
  if(root->key[0]==0)
  { root->key[0]=k;return ; }
  else if(k<t->key[0]&&notleafnode(t)){
    insert(t->link[0],k);}
  else if(k>t->key[0]&&(k<t->key[1]||t->key[1]==0)&&notleafnode(t))
    insert(t->link[1],k);
    else if(k>t->key[1]&&(k<t->key[2]||t->key[2]==0)&&notleafnode(t))
    insert(t->link[2],k);
    else if(k>t->key[2]&&(k<t->key[3]||t->key[3]==0)&&notleafnode(t))
    insert(t->link[3],k);
    else if(k>t->key[3]&&notleafnode(t))
    insert(t->link[4],k);
if(!overflow(t)&&!notleafnode(t))
{
int i;
  for(i=0;i<4;i++)
  if(t->key[i]==0)
  break;
  t->key[i]=k;
  for(int j=0;j<i+1;j++)
  {
    for(int h=j;h<i+1;h++)
    if(t->key[h]<t->key[j])
    swap(t->key[h],t->key[j]);
  }
  flag=0;
return;
  }
  if(overflow(t)&&!notleafnode(t))
    {
    for(int i=0;i<4;i++)
    temp[i]=t->key[i];
    temp[4]=k;
    sort();
    split(t);
    if(t==root)
    {
      bnode * y=new bnode();
      y->key[0]=median;
      y->link[0]=t;
      y->link[1]=(bnode*)curr;
      root=y;
flag=0;
      return ;

    }
    flag=1;
return;
    }
if(flag==1)
  {
sort_median(t,median);
return ;
  }
}
void btree::split(bnode*t1)
{
  bnode* t2=new bnode();
  t1->key[0]=temp[0];
  t1->key[1]=temp[1];
  t2->link[0]=NULL;
  t2->link[1]=t1->link[3];
  t2->link[2]=t1->link[4];
  t1->link[3]=NULL;
  t1->link[4]=NULL;
  t1->key[2]=0;
  t1->key[3]=0;
  t2->key[0]=temp[3];
  t2->key[1]=temp[4];
  curr=(void*)t2;
}
void btree::splitnonleaf(bnode* t)
{int i;
bnode*t2=new bnode();
t2->key[0]=temp[3];
t2->key[1]=temp[4];
t2->key[2]=0;
t2->key[3]=0;
  for(i=0;i<5;i++)
  if(t->key[i]>median)
  break;
  if(i<2)
  {t2->link[0]=t->link[2];
  t2->link[1]=t->link[3];
  t2->link[2]=t->link[4];
  t2->key[0]=t->key[2];
  t2->key[1]=t->key[3];
if(i==0){
      t->key[1]=t->key[0];
      t->link[2]=t->link[1];
      t->key[0]=median;
      t->link[1]=(bnode*)curr;
      }
      else {
      t->key[1]=median;
      t->link[2]=(bnode*)curr;
            }
      t->key[2]=0;
      t->key[3]=0;
       t->link[3]=NULL;
      t->link[4]=NULL;
  }
  else if(i>=2)
  {
    t2->key[0]=t->key[2];
      t2->key[1]=t->key[3];
      t2->link[0]=t->link[3];
      t2->link[1]=t->link[4];

  if(i==2)
  {t2->link[2]=t2->link[1];
    t2->link[1]=(bnode*)curr;
    t2->key[0]=median;
    }
    else
    {
      t2->key[0]=t2->key[1];
      t2->key[1]=median;
      t2->link[2]=(bnode*)curr;
     }
  t2->link[3]=NULL;
  t2->link[4]=NULL;
  t2->key[2]=0;
  t2->key[4]=0;
  t->link[2]=0;
  t->link[3]=0;
  t->link[3]=NULL;
  t->link[4]=NULL;
  }

  curr=(void*)t2;
}
void btree::sort_median(bnode*t,int m)
{int i;
if(!overflow(t))
{
  for(i=0;i<4;i++)
  if(t->key[i]==0)
  break;
  else if(t->key[i]>median)
  break;
  for(int j=3;j>i;j--){
  t->key[j]=t->key[j-1];
  t->link[j+1]=t->link[j];
  }

  t->key[i]=median;

  t->link[i+1]=(bnode*)curr;

  median=0;
  flag=0;
  return ;
}
if(overflow(t))
{
    for(int i=0;i<4;i++)
    temp[i]=t->key[i];
    temp[4]=median;
int y=median;

    sort();
    median=y;
splitnonleaf(t);
median=temp[2];
    if(t==root)
    {
      bnode * y=new bnode();
      y->key[0]=median;
      y->link[0]=t;
      y->link[1]=(bnode*)curr;
      root=y;

      return ;

    }
    flag=1;
return;
    }
}
void btree::print(bnode* t)
{cout<<"\n\n\t\t\t\t \t*********************\tbtree \t****************************\n\n";
 inqueue(root);
 int count=1;
int ncount=1;
int level=0;
for(int i=0;i<30;i++)
cout<<"  ";
  while(count&&queuenotempty())
  {
    bnode* t=dqueue();count--;
  for(int i=0;i<4;i++)
if(t->key[i]!=0){
cout<<t->key[i]<<" ";ncount++;}
cout<<"      ";
  for(int i=0;i<5;i++)
  if(t->link[i]!=NULL){
  inqueue(t->link[i]);level++;
  }
if(count==0){
count=level;
level=0; cout<<endl<<endl<<"\n\n";
for(int m=0;m<30-ncount*2;m++)
cout<<"  ";}
  }
cout<<endl;

}
bool btree::queuenotempty()
{
  if(head!=NULL)
  return true;
  else return false;
}
void btree::inqueue(bnode* t)
{
  if(head==NULL)
{head=new qnode();
 head->q=t;
  head->next=NULL;
  return ;
}qnode* e=head;
  while(e->next!=NULL)
e=e->next;
qnode* f=new qnode();
f->q=t;
f->next=NULL;
e->next=f;
return;
}
btree::~btree()
{
  inqueue(root);
  while(queuenotempty())
{bnode* t=dqueue();
if(t!=NULL)
for(int i=0;i<5;i++)
if(t->link[i]!=NULL)
{inqueue(t->link[i]);t->link[i]=NULL;}
delete(t);
}
}
struct bnode* btree::dqueue()
{bnode* b;
  if(head->next==NULL)
{b=head->q;

head=NULL;
  return b;
}
b=head->q;
head=head->next;
return b;

}
void swap(int &p,int &r)
{
  int l;
  l=p;
  p=r;
  r=l;
}
void btree::insertintobtree(int a)
{
  insert(root,a);
}
void btree::printlevelorder()
{
  print(root);
}
int main()
{btree bt;

bt.insertintobtree(5);
bt.insertintobtree(8);
bt.insertintobtree(3);
bt.insertintobtree(4);
bt.printlevelorder();
bt.insertintobtree(10);
bt.printlevelorder();


bt.insertintobtree(6);
bt.printlevelorder();

bt.insertintobtree(11);
bt.insertintobtree(2);
bt.insertintobtree(1);
bt.printlevelorder();
bt.insertintobtree(12);
bt.printlevelorder();
//bt.insertintobtree(19);
bt.printlevelorder();

bt.insertintobtree(-1);
bt.printlevelorder();
bt.insertintobtree(-2);
bt.printlevelorder();
bt.insertintobtree(-3);
bt.printlevelorder();
bt.insertintobtree(-4);
bt.printlevelorder();
bt.insertintobtree(-5);
bt.printlevelorder();
bt.insertintobtree(-6);
bt.printlevelorder();
bt.insertintobtree(-8);
bt.printlevelorder();
bt.insertintobtree(-9);
bt.printlevelorder();
bt.insertintobtree(-10);
bt.printlevelorder();
bt.insertintobtree(-11);
bt.printlevelorder();
bt.insertintobtree(-12);
bt.insertintobtree(19);
bt.printlevelorder();
bt.insertintobtree(-13);
bt.printlevelorder();
bt.insertintobtree(-14);
bt.printlevelorder();
bt.insertintobtree(-15);
//bt.printlevelorder();
bt.insertintobtree(-16);
//bt.printlevelorder();
bt.insertintobtree(-17);
//bt.printlevelorder();
bt.insertintobtree(-18);
//bt.printlevelorder();
bt.insertintobtree(19);
bt.insertintobtree(-19);
bt.insertintobtree(-20);
bt.printlevelorder();


bt.printlevelorder();
bt.insertintobtree(29);
bt.printlevelorder();
system("clear");
for(int i=0;i<100;i++)
bt.insertintobtree(100+i);

bt.printlevelorder();

return 0;
}

