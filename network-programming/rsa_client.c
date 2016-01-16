#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>
#include<gmp.h>

char  *public_key,*private_key,*n_value;
void rsa()
{
mpz_t one,two,e,d,n,p,q,temp,phi;
mpz_init(one);
mpz_init(two);
mpz_init(e);
mpz_init(d);
mpz_init(n);
mpz_init(p);
mpz_init(q);
mpz_init(temp);
mpz_init(phi);

gmp_randstate_t state

gmp_randinit_default(state);

mpz_urandomb(temp,state,16);
mpz_nextprime(p,temp);
gmp_printf("P  value is %Zd\n",p);
mpz_urandomb(temp,state,16);
mpz_nextprime(q,temp);
gmp_printf("Q value  is  %Zd\n",q);
mpz_mul(n,p,q);
mpz_set_ui(one,1);
mpz_sub(p,p,one);
mpz_sub(q,q,one);
mpz_mul(phi,p,q);

mpz_set_ui(two,2);
mpz_set(e,two);

mpz_init(temp);

mpz_gcd(temp,e,phi);
while(mpz_cmp(temp,one)!=0)
{
mpz_add(e,e,one)
mpz_init(temp);
mpz_gcd(temp,e,phi);
}

gmp_printf("E  vale  is  %Zd",e);

mpz_invert(d,e,phi);

gmp_printf("D value  is %Zd",d);

mpz_get_str(public_key,e,10);
mpz_get_str(private_key,d,10);

mpz_get_str(n_value,n,10);

}



int main()
{

int a=fork();
if(a==0)
{
int sfd1;
char  buf[100];
sfd1=socket(AF_INET,SOCT_STREAM,0);
if(sfd1==-1)
{

printf("socket error \n");
exit(1);

}
struct sockaddr_in send_key;
bzero((char*)&send_key,sizeof(send_key));
send_key.sin_family=AF_INET;
send_key.sin_addr.s_addr=addr_addr("127.0.0.1");
send_key.sin_port=htons(1500);

int c=connect(sfd1,(struct sockaddr *)&send_key,sizeof(send_key));
if(c<0)
{
printf("connection error\n");
exit(1);
}

void rsa();

strcpy(buf,public_key);
send(sfd1,buf,strlen(buf),0);
memset(buf,0,100);
strcpy(buf,n_value);
send(sfd1,buf,strlen(buf),0);
}


else

{









}


}
