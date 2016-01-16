//implementing key exchange using Diffie-Hellman
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<gmp.h>

mpz_t gen;


void find_generator(mpz_t q)
{
mpz_t test;
mpz_init(test);
char st[20];
int i;
int max;
gmp_sprintf(st,"%Zd",q);
max=atoi(st);
for(i=2;i<max;i++)
{
int arr[100]={0};
sprintf(st,"%d",i);
mpz_set_str(test,st,10);
int j;
for(j=1;j<max;j++)
{
mpz_t res;
mpz_init(res);
mpz_t exp;
mpz_init(exp);
sprintf(st,"%d",j);
mpz_set_str(exp,st,10);
mpz_powm(res,test,exp,q);
//printf("ok1\n");
gmp_sprintf(st,"%Zd",res);
arr[atoi(st)]=1;
//printf("fine\n");
}
for(j=1;j<max;j++)
if(arr[j]==0)
goto beg;
printf("setting gen value\n");
mpz_set(gen,test);
return;
beg:
;
}
}


int main()
{
gmp_randstate_t state;
gmp_randinit_mt(state);
mpz_t limit;
mpz_init(limit);
mpz_set_str(limit,"91",10);
mpz_t p;
mpz_init(p);
//setting value to p
mpz_urandomm(p,state,limit);
mpz_nextprime(p,p);
mpz_init(gen);
find_generator(p);
gmp_printf("generator= %Zd and q=%Zd\n",gen,p);
mpz_t x;
mpz_init(x);
mpz_urandomm(x,state,p);
mpz_t y;
mpz_init(y);
mpz_powm(y,gen,x,p);
gmp_printf("key to be transmitted= %Zd\n",y);
char st[100];
printf("enter public key of other peer\n");
scanf("%s",st);
mpz_set_str(y,st,10);
mpz_t key;
mpz_init(key);
mpz_powm(key,y,x,p);
gmp_printf("resultant key is %Zd\n",key);
return 0;
}
