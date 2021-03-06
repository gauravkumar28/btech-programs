#include<iostream>
#include<gmp.h>

using namespace std;
 int main(int argc,char **argv)
 {
mpz_t n,p,q,temp,phi,one,e,res,d,c,m;
mpz_init(n); 
mpz_init(p);
mpz_init(q);
mpz_init(temp);
mpz_init(phi);
mpz_init(e);
mpz_init(res);
mpz_init(d);
mpz_init(c);
mpz_init(m);
gmp_randstate_t state; 
gmp_randinit_default(state);
mpz_urandomb(temp,state,16);
mpz_nextprime(p,temp); 
gmp_printf("prime  p is %Zd\n",p);
mpz_urandomb(temp,state,16);
mpz_nextprime(q,temp);
gmp_printf("prime  q is %Zd\n",q);
mpz_mul(n,p,q);
gmp_printf("n value  is %Zd\n",n);
mpz_init(one); 
mpz_set_ui(one,1);
mpz_sub(p,p,one);
//gmp_printf("%Zd\n",p);
mpz_sub(q,q,one);
mpz_mul(phi,p,q);
/*mpz_t tmp;
mpz_init(tmp);
mpz_sub(tmp,phi,one);*/
mpz_t two;
mpz_init(two);
mpz_set_ui(two,2);
mpz_set(e,two);
mpz_gcd(temp,e,phi);
//gmp_printf("%Zd\n",temp);
while(mpz_cmp(temp,one)!=0)
{
mpz_add(e,e,one);
mpz_init(temp);
mpz_gcd(temp,phi,e);
}
gmp_printf("e  value  is %Zd\n",e);
mpz_invert(d,e,phi);
gmp_printf("secret key is %Zd\n",d);
mpz_urandomb(m,state,8);
gmp_printf("message before encryption is %Zd\n",m);
mpz_powm(c,m,e,n);
gmp_printf("message after encryption is %Zd\n",c);
mpz_powm(m,c,d,n);
gmp_printf("message after decrption is %Zd\n",m);
}
