#include<stdio.h>
#include<sys/socket.h>
#include<netdb.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<string.h>
#include<stdlib.h>
#include<gmp.h>




int main()
{
int sfd;
char  public_key[100];
char private_key[100];
char n_value[100];
char  buf[100];

if((sfd=socket(AF_INET,SOCK_STREAM,0))==-1)
{
printf("\n socket error \n");
exit(1);

}

struct sockaddr_in client;
bzero((char *)&client,sizeof(client));
client.sin_family=AF_INET;
client.sin_addr.s_addr=inet_addr("127.0.0.1");
client.sin_port=htons(1500);

int a=connect(sfd,(struct sockaddr *)&client,sizeof(client));
if(a<0)
{
printf(" connection error\n");
exit(1);


}
 //rsa();
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

gmp_randstate_t state;

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
mpz_add(e,e,one);
mpz_init(temp);
mpz_gcd(temp,e,phi);
}

gmp_printf("E  vale  is  %Zd\n",e);

mpz_invert(d,e,phi);

gmp_printf("D value  is %Zd\n",d);
mpz_get_str(public_key,10,e);
mpz_get_str(private_key,10,d);

mpz_get_str(n_value,10,n);

//while(1)
{
strcpy(buf,public_key);
printf("public key is %s \n",public_key);
send(sfd,buf,strlen(buf),0);
memset(buf,0,100);
strcpy(buf,n_value);
printf("n_value is  %s\n",n_value);
send(sfd,buf,strlen(buf),0);
}
}





