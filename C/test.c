#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define ll long long int
#define LL long long int
#define ui unsigned int
#define uLL unsigned long long int

typedef struct test
{
    int a;
    int b;
    double c;
} test;

int main()
{
    struct test *t;
    int a;
    int b;
    double c;
    t = (test *)malloc(4 * sizeof(test));
    for (int i = 0; i < 4; i++)
    {
        scanf("%d%d%lf", &a, &b, &c);
        t[i].a = a;
        t[i].b = b;
        t[i].c = c;
    }
    return 0;
}