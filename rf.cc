#include <stdio.h>
int rf(int n);
int main()
{
           printf("%d\n", rf(6));
                  return 0;
}
int rf(int n)
{
          if(n<=2) return 1;
                return rf(n-1)+ rf(n-2);
}
