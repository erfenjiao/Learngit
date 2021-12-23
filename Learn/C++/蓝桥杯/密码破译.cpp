#include<iostream>
using namespace std;

int main()
{
    char a[100];
    cin >> a;
    int i = 0;
    while(a[i] != '\0')
    {
        printf("%c",a[i]+4);
        i++;
    }
}