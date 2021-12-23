#include<stdio.h>


int main()
{
    int k;
    scanf("%d",&k);
    int a[k];
    for(int i=0;i<k;i++)
    {
        scanf("%d",&a[i]);
    }
    int max=0,sum=0;
    for(int i=0;i<k;i++)
    {
        sum=0;
        for(int j=i;j<k;j++)
        {
            sum+=a[j];
            if(sum > max)
            {
                max = sum;
            }
        }
    }
    printf("%d",max);
}