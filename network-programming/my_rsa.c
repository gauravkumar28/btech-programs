#include<stdio.h>
#include<gmp.h>

int main()
{

mpz_t one,two,e,d,p,q,n,c,m,temp,phi;
mpz_init(one);
mpz_init(two);
mpz_init(e);
mpz_init(d);
mpz_init(p);
mpz_init(q);
mpz_init(n);
mpz_init(c);
mpz_init(m);
mpz_init(temp);
mpz_init(phi);

gmp_randstate_t state;
gmp_randinit_default(state);
mpz_urandomb(temp,state,16);
mpz_nextprime(p,temp);
mpz_init(temp);
mpz_urandomb(temp,state,16);
mpz_nextprime(q,temp);
gmp_printf("P valeu is %Zd\n",p);
gmp_printf("q value is %Zd\n",q);
mpz_mul(n,p,q);
gmp_printf("n value is %Zd\n",n);
mpz_set_ui(one,1);
mpz_sub(p,p,one);
mpz_sub(q,q,one);
mpz_mul(phi,p,q);

mpz_set_ui(two,2);

mpz_set(e,two);
mpz_gcd(temp,phi,e);
while( mpz_cmp(temp,one)!=0)
{
mpz_add(e,e,one);
mpz_init(temp);
mpz_gcd(temp,e,phi);
}

gmp_printf(" the  e value is %Zd\n",e);

mpz_invert(d,e,phi);

gmp_printf("\n the  d value  is %Zd\n",d);
int message;
printf("enter the message  to encriypt\n");
scanf("%d",&message);
mpz_set_ui(m,message);
//mpz_urandomb(m,state,8);


//gmp_printf("message  is  %Zd\n",m);
mpz_powm(c,m,e,n);
//gmp_printf("message after encryption is %Zd\n",c);
char *s;
mpz_get_str(s,10,c);
printf("the  incripted message is  %s\n",s);
mpz_powm(m,c,d,n);
mpz_get_str(s,10,m);
gmp_printf("message after decription is %s\n",s);




}


