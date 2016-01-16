#include<iostream>
using namespace std;
void* cur;
int flag=0,flag2=0;
int temp[5];

struct qnode
{struct bnode* q;
  qnode* next;
}*head=NULL;

struct bnode
{int key[4];
int counter;
struct bnode* link[5];
}*root=NULL,*parent=NULL;

int median=0;
bool overflow(struct bnode* t)
{
  if(t->counter>=4)
  return true;
  else return false;
}
void split_leaf(struct bnode* t,struct bnode* p)
{bnode* t1;
cout<<"\n-----------------------\n";
t1=new bnode();
t1->key[0]=temp[3];
t1->key[1]=temp[4];
t1->counter=2;
t->counter=2;
for(int i=0;i<5;i++)
t1->link[i]=NULL;
cur=(void*)t1;
  if(p==NULL)
  {p=new bnode();//cout<<"%%%%%%%%%%%%%%%%";
  p->link[0]=t;
  p->key[0]=temp[2];
  p->link[1]=t1;
  p->counter=1;
  root=p;
  flag=0;
 // cout<<"00000000000000000";
   return;
  }
  else if(!overflow(p))
  {//cout<<"#####################";
  int i;
  for(i=0;i<p->counter;i++)
  if(p->key[i]>temp[2])
  break;
  for(int j=p->counter;j>i;j--)
  {p->link[j+1]=p->link[j];
  p->key[j]=p->key[j-1];
  }
  p->key[i]=temp[2];
  p->link[i+1]=t1;
  p->counter=p->counter+1;
  cout<<p->counter;
  flag=0;
  return;
  }
  else if(overflow(p))
  {int i;
  cout<<"overflwo dude";
struct  bnode* px=new bnode();
    for(i=0;i<4;i++)
  if(t->key[i]>temp[2])
  break;
  cout<<"valuse of i is"<<i;
  if(i<2)
  {px->link[0]=p->link[2];
  px->link[1]=p->link[3];
  px->link[2]=p->link[4];
  px->key[0]=p->key[2];
  px->key[1]=p->key[3];
  median=p->key[1];
if(i==0){
      p->key[1]=p->key[0];
      p->link[2]=p->link[1];
      p->key[0]=temp[2];
      p->link[1]=t1;
      }
      else {
      p->key[1]=temp[2];
      p->link[2]=t1;
            }
      p->key[2]=0;
      p->key[3]=0;
       p->link[3]=NULL;
      p->link[4]=NULL;
  }
  else if(i>=2)
  {
    px->key[0]=p->key[2];
      px->key[1]=p->key[3];
      px->link[0]=p->link[3];
      px->link[1]=p->link[4];
median=p->key[2];
  if(i==2)
  {px->link[2]=px->link[1];
    px->link[1]=t1;
    px->key[0]=temp[2];
    }
    else
    {
      px->key[0]=px->key[1];
      px->key[1]=temp[2];
      px->link[2]=t1;
     }
 px->link[3]=NULL;
  px->link[4]=NULL;
  px->key[2]=0;
  px->key[4]=0;
  p->key[2]=0;
  p->key[3]=0;
  p->link[3]=NULL;
  p->link[4]=NULL;

  }
px->counter=2;
  p->counter=2;
  cout<<"))))))))))))))))";
  cout<<px->link[1]->key[0];
  cur=(void*)px;
  flag++;return ;
  cout<<"}}}}}}}}}}}}";
}

}
void sort()
{
 for( int i=0;i<5;i++)
  for(int j=i;j<5;j++)
  if(temp[i]>temp[j])
  swap(temp[i],temp[j]);
  return ;
}
void swap(int &x,int &y)
{
  int z;
  z=x;
  x=y;
  y=z;
  return;
}

bool leafnode(struct bnode* t)
{int i;
  for(i=0;i<5;i++)
  if(t->link[i]!=NULL)
  break;
  if(i==5)
  return true;
  else return  false;
}

void split_nonleaf(struct bnode* t,struct bnode* p)
{
  if(p==NULL&&flag==1)
  {
cout<<"rammmmmmmmmmmmmmmmm";
    bnode* p=new bnode();
    p->link[0]=t;
    p->link[1]=(bnode*)cur;
    p->key[0]=median;
    median=0;
    p->counter=1;
    root=p;
    flag=0;
    return ;
  }
  else if(!overflow(p))
  {/*int i;
    for(i=0;i<=p->counter;i++)
    if(p->link[i]==t)
    break;

int xx=temp[2];

if(!overflow(p->link[i-1]))
{int j;
  for(j=0;j<4;j++)
if(t->key[j]>temp[2])
break;
p->link[i-1]->link[p->link[i-1]->counter+1]=t->link[0];
p->link[i-1]->key[p->link[i-1]->counter++]=p->key[i-1];
p->key[i-1]=t->key[0];
for(int k=0;k<j;k++){
t->key[k]=t->key[k+1];
t->link[k]=t->link[k+1];}
t->key[j]=temp[2];
t->link[j]=t->link[j+1];
t->link[j+1]=(bnode*)cur;
 return;
}

else if(!overflow(p->link[i+1]))
{
  int j;
  for(j=0;j<4;j++)
if(t->key[j]>temp[2])
break;
p->link[i+1]->link[p->link[i+1]->counter+1]=p->link[i+1]->link[p->link[i+1]->counter];
for(int k=p->link[i+1]->counter;k>0;k--)
{p->link[i+1]->link[k]=p->link[i+1]->link[k-1];
p->link[i+1]->key[k]=p->link[i+1]->key[k-1];
}
p->link[i+1]->counter++;
p->link[i+1]->key[0]=p->key[i];
p->link[i+1]->link[0]=p->link[i]->link[p->link[i]->counter];
p->key[i]=p->link[i]->key[p->link[i]->counter-1];
for(int k=t->counter;k>j;k--){
t->key[k]=t->key[k-1];
t->link[k+1]=t->link[k];}
t->key[j]=temp[2];
t->link[j+1]=(bnode*)cur;
return;
}




















*/





































































int i;
    cout<<"munny  badnamm hui";

    cout<<"median is"<<median;
  for(i=0;i<p->counter;i++)
  if(p->key[i]>median)
  break;
  cout<<i;
  for(int j=p->counter;j>i;j--)
  {p->link[j+1]=p->link[j];
  p->key[j]=p->key[j-1];
  }
  p->key[i]=median;
  p->link[i+1]=(bnode*)cur;
  p->counter=p->counter+1;
  flag=0;
  return;
  }
  else if(overflow(p))
  {int i;
  bnode* px=new bnode();
    for(i=0;i<5;i++)
  if(t->key[i]>median)
  break;
  int xx=median;
  if(i<2)
  {px->link[0]=p->link[2];
  px->link[1]=p->link[3];
  px->link[2]=p->link[4];
  px->key[0]=p->key[2];
  px->key[1]=p->key[3];
  median=p->key[1];
if(i==0){
      p->key[1]=p->key[0];
      p->link[2]=p->link[1];
      p->key[0]=xx;
      p->link[1]=(bnode*)cur;
      }
      else {
      p->key[1]=xx;
      p->link[2]=(bnode*)cur;
            }
      p->key[2]=0;
      p->key[3]=0;
       p->link[3]=NULL;
      p->link[4]=NULL;
  }
  else if(i>=2)
  {
    px->key[0]=p->key[2];
      px->key[1]=p->key[3];
      px->link[0]=p->link[3];
      px->link[1]=p->link[4];
median=p->key[2];
  if(i==2)
  {px->link[2]=px->link[1];
    px->link[1]=(bnode*)cur;
    px->key[0]=median;
    }
    else
    {
      px->key[0]=px->key[1];
      px->key[1]=median;
      px->link[2]=(bnode*)cur;
     }
 px->link[3]=NULL;
  px->link[4]=NULL;
  px->key[2]=0;
  px->key[4]=0;
  p->key[2]=0;
  p->key[3]=0;
  p->link[3]=NULL;
  p->link[4]=NULL;

  }
px->counter=2;
  p->counter=2;
  cur=(void*)px;
  flag=1;return ;
}
}
bool queuenotempty()
{
  if(head!=NULL)
  return true;
  else return false;
}
struct bnode* dqueue()
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
void key_redistibution(struct bnode* t,struct bnode* p)
{int i;
cout<<"key  redist";
  for( i=0;i<=p->counter;i++)
  if(p->link[i]==t)
  break;
  cout<<i;
  if(i==0&&overflow(p->link[i+1])){flag2=1;
  return;}
  else if(i==0&&!overflow(p->link[i+1]))
          { int zz=p->key[i];

        p->link[i+1]->key[p->link[i+1]->counter++]=zz;
        p->key[i]=temp[4];
        for(int i=0;i<4;i++)
        t->key[i]=temp[i];
        for(int j=0;j<p->link[i+1]->counter;j++)
        {
          for(int k=j;k<p->link[i+1]->counter;k++)
          if(p->link[i+1]->key[j]>p->link[i+1]->key[k])
          swap(p->link[i+1]->key[j],p->link[i+1]->key[k]);
        }

        flag2=0;
        return;
          }
          else if(i==p->counter&&overflow(p->link[i-1]))
         {
           flag2=1;return;}
          else if(i==p->counter&&!overflow(p->link[i-1]))
          {
            int zz=p->key[i-1];

            p->link[i-1]->key[p->link[i-1]->counter++]=zz;
        p->key[i-1]=temp[0];
        cout<<p->key[i-1];
        for(int i=0;i<4;i++)
        t->key[i]=temp[i+1];
       for(int j=0;j<4;j++)
       cout<<t->key[j];
        flag2=0;
        return;
          }
else
{
  if(!overflow(p->link[i+1]))
  {
   int zz=p->key[i];

        p->link[i+1]->key[p->link[i+1]->counter++]=zz;
        p->key[i]=temp[4];
        for(int i=0;i<4;i++)
        t->key[i]=temp[i];
        for(int j=0;j<p->link[i+1]->counter;j++)
        {
          for(int k=j;k<p->link[i+1]->counter;k++)
          if(p->link[i+1]->key[j]>p->link[i+1]->key[k])
          swap(p->link[i+1]->key[j],p->link[i+1]->key[k]);
        }

        flag2=0;
        return;
  }
  else if(!overflow(p->link[i-1]))
  {
   int zz=p->key[i-1];

            p->link[i-1]->key[p->link[i-1]->counter++]=zz;
        p->key[i-1]=temp[0];
        cout<<p->key[i-1];
        for(int i=0;i<4;i++)
        t->key[i]=temp[i+1];
       for(int j=0;j<4;j++)
       cout<<t->key[j];
        flag2=0;
        return;
  }



}
}
void insert(struct bnode*& t,struct bnode*& p,int key)
{if(t==NULL)
{cout<<"sexy;;;;;;";
  t=new bnode();
t->key[0]=key;
t->counter=1;
for(int i=0;i<5;i++)
t->link[i]=NULL;
root=t;

return ;
}
else if(key<t->key[0]&&!leafnode(t))
insert(t->link[0],t,key);
else if(key>t->key[0]&&(key<t->key[1]||t->counter==1)&&!leafnode(t)){cout<<"&&&&&&&&&&&&&&&&&&";
insert(t->link[1],t,key);}
else if(key>t->key[1]&&(key<t->key[2]||t->counter==2)&&!leafnode(t))
insert(t->link[2],t,key);
else if(key>t->key[2]&&(key<t->key[3]||t->counter==3)&&!leafnode(t))
insert(t->link[3],t,key);
else if(key>t->key[3]&&!leafnode(t)){cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>";
insert(t->link[4],t,key);}
if(!overflow(t)&&leafnode(t))
{

  cout<<"key is"<<t->key[0];
  t->key[t->counter++]=key;

  for(int i=0;i<t->counter;i++)
  {
    for(int j=i;j<t->counter;j++)
    if(t->key[i]>t->key[j])
    swap(t->key[i],t->key[j]);
  }
 flag=0; return;
}
if(overflow(t)&&leafnode(t))
{for(int i=0;i<t->counter;i++)
temp[i]=t->key[i];
temp[t->counter]=key;
sort();
flag2=1;
  for(int i=0;i<=t->counter;i++)
  cout<<temp[i]<<"  ";
if(p!=NULL)
{
  key_redistibution(t,p);
}
if(flag2==1)
split_leaf(t,p);
cout<<"}}}}}}}}}}}}}}}}}}}}";
  return;
}
if(flag>0)
{cout<<"\n parent overflow\n";
for(int i=0;i<t->counter;i++)
cout<<t->key[i];
cout<<median;
if(p==NULL)
cout<<"rarrrrr";
  split_nonleaf(t,p);return;
  flag=0;
}

}

void inqueue(bnode* t)
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

void print(bnode* t)
{cout<<"\n\n *********************\tbtree \t****************************\n\n";
 inqueue(root);
 int count=1;
int level=0;
for(int i=0;i<30;i++)
cout<<"  ";
  while(count&&queuenotempty())
  {
    bnode* t=dqueue();count--;
  for(int i=0;i<t->counter;i++)
cout<<t->key[i]<<" ";
cout<<"      ";
  for(int i=0;i<t->counter+1;i++)
  if(t->link[i]!=NULL){
  inqueue(t->link[i]);level++;
 }
if(count==0){
count=level;

level=0; cout<<endl<<endl<<"---------------------------------------------------------------------------\n\n";
for(int m=0;m<30-count*2;m++)
cout<<"  ";
}
  }
cout<<endl;

}
int main()
{int k;
for(int i=0;i<100;i++){
insert(root,parent,i);
print(root);
}
/*
insert(root,parent,5);
insert(root,parent,10);
insert(root,parent,14);
insert(root,parent,100);
insert(root,parent,20);
insert(root,parent,4);
insert(root,parent,3);
insert(root,parent,2);
print(root);/*
insert(root,parent,141);
insert(root,parent,151);
insert(root,parent,161);
insert(root,parent,171);
insert(root,parent,181);
insert(root,parent,191);
insert(root,parent,201);
insert(root,parent,211);
insert(root,parent,221);
insert(root,parent,231);
insert(root,parent,241);
insert(root,parent,251);
insert(root,parent,261);
insert(root,parent,271);
insert(root,parent,281);
insert(root,parent,291);
insert(root,parent,301);
insert(root,parent,311);
for(int i=0;i<30;i++)
insert(root,parent,311+i+1);
print(root);
/*insert(root,parent,-22);
insert(root,parent,200);
insert(root,parent,300);
insert(root,parent,305);
insert(root,parent,307);
insert(root,parent,400);
insert(root,parent,405);
insert(root,parent,410);
insert(root,parent,415);
insert(root,parent,425);
insert(root,parent,430);
insert(root,parent,435);
insert(root,parent,-100);
insert(root,parent,-200);
insert(root,parent,-400);
insert(root,parent,-300);
insert(root,parent,-500);
insert(root,parent,-600);
insert(root,parent,-700);
insert(root,parent,-800);
insert(root,parent,-900);
insert(root,parent,12345);
cout<<endl;
for(int i=0;i<1000;i++)
insert(root,parent,2000+i);
//cout<<root->key[0];
//cout<<root->link[0]->counter;*/
//print(root);



return 0;
}
