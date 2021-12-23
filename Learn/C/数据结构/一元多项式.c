//乘积与和
#include<stdio.h>
#define N 10000
int main()
{
    int a[N];
    int b[N];
    int c[N];   //*
    int d[N];   //+
    int n , x, z;
    scanf("%d",&n);
    while(n--)
    {
        scanf("%d %d",&x , &z);
        a[z] += x;     //指数为z的系数放在z位置上
    }
    scanf("%d",&n);
    while(n--)
    {
        scanf("%d %d",&x , &z);
        b[z] += x;     //指数为z的系数放在z位置上
    }

    //*
    for(int i=N-1;i>=0;i--)
    {
        if(a[i])
        {
            for(int j=0;j<N;j++)
            {
                if(b[j])
                {
                    c[i+j] += a[i]*b[j];
                }
            }
        }
    }
    int cnt = 0;
    for(int i=N-1;i>=0;i--)
    {
        if(cnt)
        {
            printf(" ");
        }
        printf("%d %d",c[i],i);
        cnt++;
    }
    if(!cnt)
    {
        printf("0 0");
    }

    //+
    for(int i=N-1;i>=0;i--)
    {
        d[i] += a[i];
    }
    for(int j=N-1;j>=0;j--)
    {
        d[j] += a[j];
    }
    cnt=0;
    for(int i=N-1;i>=0;i--)
    {
        if(d[i])
        {
            if(cnt)
            {
                printf(" ");
            }
            printf("%d %d",d[i] , i);
            cnt++;
        }
    }
    if(!cnt)
    {
        printf("0 0");
    }
}