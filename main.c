/*# include <stdio.h>
void hello(){
    printf ("hello world\n");
}
int main ()
{
    float a=1.2234;
    char  x='A';
    printf("%d %o %x %f", x,x,x,a);


}*/
#include <stdio.h>/*
void f (int x, int y) {
  while (x < y) {
    printf("%d ", y - x);
    x = x + 1;
    y = y - 1;
  }
}
int main()
{
    f(-1,4);
   /**int k,n;
    n=2;
    float sum=1;

    scanf("%d",&k);
    if(k>= 1 &&k<=15)
    {
        while(sum< k)
        {
            sum=sum+1.0/n;
            n++;

        }
        printf("%d",n);

    }
    else
        printf("error\n");
    return 0;
}
*/

int main (void) {
  int a = 2;
  int b = 6;
  while (a <= b) {
    if (a % 2 == 1) {
      printf("a is %d\n", a);
    }
    else {
      printf("b is %d\n", b);
      for (int i = 0; i < b - a ; i++) {
        printf("a * i + b = %d\n", a * i + b);
      }
    }
    a++;
    b--;
  }
  return 0;
}