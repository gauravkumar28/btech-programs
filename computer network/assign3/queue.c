
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<malloc.h>
struct qnode
{

struct node* b;
struct qnode* next;
}*head=NULL;


int isempty()
{
if(head==NULL)
return 1;
else return 0;
}

void inqueue(struct node* b)
{


if(head==NULL)
{
head=(struct qnode*)(malloc(sizeof(struct qnode)));
head->b=b;
head->next=NULL;
return;}

struct qnode* q;
q=head;
while(q->next!=NULL)
q=q->next;
struct qnode* p=(struct qnode*)(malloc(sizeof(struct qnode)));
p->next=NULL;
p->b=b;
q->next=p;
return ;
}
struct node* dqueue()

{
if(head!=NULL){
struct qnode* x;
x=head;
head=head->next;
return x->b;}
else
return NULL;


}


