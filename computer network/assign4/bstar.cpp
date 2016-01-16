int i;
  cout<<"overflwo dude";
struct  bnode* px=new bnode();
    for(i=0;i<4;i++)
  if(t->key[i]>temp[3])
  break;
  cout<<"valuse of i is"<<i;
  if(i<3)
  {px->link[0]=p->link[3];
  px->link[1]=p->link[4];
  px->key[0]=p->key[3];
  median=p->key[2];
  for(int k=2;k>i;k--)
  {
    p->link[k+1]=p->link[k];
    p->key[k]=p->key[k-1];
  }
  p->link[i+1]=t1;
  p->key[i]=temp[3];/*
if(i==0){
      p->key[1]=p->key[0];
      p->link[2]=p->link[1];
      p->key[0]=temp[3];
      p->link[1]=t1;
      }
      else {
      p->key[1]=temp[3];
      p->link[2]=t1;
            }
      p->key[2]=0;
      p->key[3]=0;
       p->link[3]=NULL;
      p->link[4]=NULL;*/
  }
  else if(i>=3)
  {      px->link[0]=p->link[4];
median=p->key[3];
 px->key[0]=temp[2];
      px->link[1]=t1;
px->link[2]=NULL;
 px->link[3]=NULL;
  px->link[4]=NULL;
  px->key[2]=0;
  px->key[4]=0;
  p->key[3]=0;
  p->link[4]=NULL;
px->key[1]=0;
  }
px->counter=3;
  p->counter=1;
  cout<<"))))))))))))))))";
  cout<<px->link[1]->key[0];
  cur=(void*)px;
  flag++;
