#include <stdio.h>

// 读取一个整数，返回值放入 EAX
int input()
{
    int x;
    scanf("%d", &x);
    return x;
}

// 输出一个整数
void output(int x)
{
    printf("%d\n", x);
}