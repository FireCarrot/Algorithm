#include <stdio.h>
#include <iostream>

using namespace std;

int f(int num);
int main()
{
        printf("%d\n", f(511));
            getchar();
                return 0;
}
int f(int num)
{
        if(num==0) return 0;
        cout << num%10;
        cout << num/10;
        cout << num/100;
        return (num%10)+f(num/10)+f(num/100);
}
