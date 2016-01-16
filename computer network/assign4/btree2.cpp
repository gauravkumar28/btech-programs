#include<stdio.h>
#include<unistd.h>
#include<string.h>
using namespace std;

struct btree
{
int key[4];
struct bnode* link[5];
int count;
}*root=NULL;

void sort(struct bnode*t)
{
for(int i=0;i<count;i++){
for(int j=i;j<count;j++)
if(t->key[i]>t->key[j])
swap(t->key[i],t->key[j]);
}

}

void swap(int &x,int &y)
{int z;
z=x;
x=y;
y=x;
return;
}
void insert(struct bnode*&t,int key)
{
if(count==0)
{t=new node();
for(int i=0;i<5;i++)
t->link=NULL;
t->key[0]=key;
t->count=1;
}
if(key<t->key[0]&&!leafnode(t))
insert(t->link[0],key);
else if(key>t->key[0]&&(key<t->key[1]||count==1)&&!leafnode(t))
insert(t->link[1],key);
else if(key>t->key[1]&&(key<t->key[2]||count==2)&&!leafnode(t))
insert(t->link[2],key);
else if(key>t->key[2]&&(key<t->key[3]||count==3)&&!leafnode(t))
insert(t->link[3],key);
else if(key>t->key[3]&&!leafnode(t))
insert(t->link[4],key);
if(!overflow(t))
{
t->key[count]=key;
count++;
sort(t);
}
else if(overflow(t))
node_split(t);
}


}
