#include<iostream>
#include<gmp.h>
using namespace std;
int main()
{
mpz_t tmp,q,g,temp,val,h,x,one,count,y,c1,c2,s,m,sm,i,zero;
mpz_init(tmp);
mpz_init(q);
mpz_init(g);
mpz_init(val);
mpz_init(h);
mpz_init(x);
mpz_init(one);
mpz_init(zero);
mpz_init(count);
mpz_init(y);
mpz_init(c1);
mpz_init(c2);
mpz_init(s);
mpz_init(m);
mpz_init(sm);
mpz_init(temp);
mpz_init(i);
mpz_set_ui(one,1);
mpz_set(i,one);
mpz_set_ui(zero,0);
mpz_set(count,zero);
gmp_randstate_t state; 
gmp_randinit_default(state);
mpz_urandomb(temp,state,16);
mpz_nextprime(tmp,temp);
gmp_printf("prime number is %Zd\n",tmp);
mpz_sub(q,tmp,one);
mpz_sub(val,q,one);
mpz_urandomb(x,state,16);
while(mpz_cmp(x,val)==0)
mpz_urandomb(x,state,16);
mpz_urandomb(g,state,8);
while(1)
{
mpz_set(count,zero);
mpz_set(i,one);
mpz_set(temp,g);
while(mpz_cmp(temp,one)!=0)
{
mpz_powm(temp,g,i,tmp);
mpz_add(i,i,one);
mpz_add(count,count,one);
}
if(mpz_cmp(count,q)==0)
{
gmp_printf("the generator is %Zd\n",g);
break;
}
else
mpz_add(g,g,one);
}
mpz_powm(h,g,x,tmp);
gmp_printf("alice's public key %Zd %Zd %Zd \n",q,g,h);
mpz_urandomb(y,state,16);
while(mpz_cmp(y,val)==0)
mpz_urandomb(y,state,16);
mpz_powm(c1,g,y,tmp);
mpz_powm(s,h,y,tmp);
gmp_printf("shared secret calculated by Bob %Zd \n",s);
mpz_urandomb(m,state,8);
mpz_mod(sm,m,q);
gmp_printf("message is %Zd \n",sm);
mpz_mul(c2,sm,s);
gmp_printf("Bob sends the cipher text %Zd %Zd \n",c1,c2);
mpz_powm(s,c1,x,tmp);
gmp_printf("shared secret calculated be Alice %Zd \n",s);
mpz_invert(temp,s,q);
mpz_mul(c2,sm,temp);
gmp_printf("Decrypted message by Alice %Zd \n",c2);
}




