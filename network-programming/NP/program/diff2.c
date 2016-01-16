
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<gmp.h>







int main()
{
gmp_randstate_t state;
gmp_randinit_mt(state);
mpz_t x,p,gen;
mpz_inits(p,x,gen,NULL);
char st[20];
printf("enter the prime number q\n");
scanf("%s",st);
mpz_set_str(p,st,10);
printf("enter the generator gen\n");
scanf("%s",st);
mpz_set_str(gen,st,10);
mpz_urandomm(x,state,p);
mpz_t y;
mpz_init(y);
mpz_powm(y,gen,x,p);
gmp_printf("key to be transmitted= %Zd\n",y);
printf("enter public key of other peer\n");
scanf("%s",st);
mpz_set_str(y,st,10);
mpz_t key;
mpz_init(key);
mpz_powm(key,y,x,p);
gmp_printf("resultant key is %Zd\n",key);
return 0;
}
