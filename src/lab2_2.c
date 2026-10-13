#include <stdio.h>

long long factorial(int n)
{
    long long result = 1;

    for (int i = 1; i <= n; i++)
    {
        result = result * i;
    }

    return result;
}

int main(void)
{
    int n;

    printf("Enter n: ");

    if (scanf("%d", &n) != 1)
    {
        printf("Error: invalid input.\n");
        return 1;
    }

    if (n < 0)
    {
        printf("Error: n cannot be negative.\n");
    }
    else
    {
        printf("Factorial = %lld\n", factorial(n));
    }

    return 0;
}
