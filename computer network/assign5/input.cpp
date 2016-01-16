#include <stdio.h>
#include <iostream>
using namespace std;
#define AREA(x) (3.14*x*x)
#define swap(a,b) {a=a+b;b=a-b;a=a-b;cout<<a<<b;}
int main()
{
float r= 6.25, s= 2.5, a ;
a=AREA(r) ;
int c=2,b=3;
swap(c,b)
printf ("\nArea of circle=%f",a);
a= AREA(s) ;
printf ("\nArea of circle=%f",a);
return 0;
}
