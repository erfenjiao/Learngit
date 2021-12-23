#include<iostream>
using namespace std;
/*
有一头母牛，它每年年初生一头小母牛。每头小母牛从第四个年头开始，每年年初也生一头小母牛。
请编程实现在第n年的时候，共有多少头母牛？
输入数据由多个测试实例组成，每个测试实例占一行，包括一个整数n(0<n<55)，n的含义如题目中
描述。
n=0表示输入数据的结束，不做处理。

--------------递归----------------(时间超限)
int ct = 1;
int fun(int n)
{
     if (n == 1)
        ct =  1;
     else if(n == 2)
        ct = 2;
     else if(n == 3)
          ct = 3;
     else
         ct = fun(n-1) + fun(n-3);
     return ct;
}
int main()
{   
    int  n;
    while(cin >> n && n!=0)
    { fun(n);
    printf("%d\n",ct);
    }  
    return 0;
}
*/
//#include <bits/stdc++.h>
int main()
{
    int a[100] = {0,1,2,3,4};
    int n;

    for(int i = 5 ; i < 100 ; i++)
    {
        a[i] = a[i-1]+a[i-3];
    }
    while(cin >> n && n)
    {
        printf("%d\n",a[n]);
    }
}
