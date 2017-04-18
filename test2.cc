#include <stdio.h>
int test(int num);
int main()
{
        printf("%d\n", test(650));
            return 0;
}
int test(int num)
{
        if(num) return num%10 + test(num/10);
            else return 0;
}
