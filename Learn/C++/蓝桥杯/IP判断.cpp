#include<iostream>
#include<stdio.h>
#include<cstring>
using namespace std;

int cinverti(char str[])
{
    int num = 1;
    int len = strlen(str);
    if(len >= 4)
        return 0;
    for(int i = 0 ; i < len ; i++)
    {
        num = num*10 + str[i]-'0';
    }
    
}

int IsIP(char str[])
{
    int i=0 , k = 0 , count = 0 , numDian = 0;
    char temp[30];
    for(i = 0 ; str[i] != '\0' ;i++)
    {
        k = 0;
        if(str[0] == '.')
            return 0;
        while(str[i] != '.' && str[i] != '\0')
        {
            if(str[i] < '0' || str[i] > '9')
                return 0;
            if(str[i] != '.' && str[i] != '\0')
                temp[k++] = str[i++];
        }
        if(str[i] == '.' && str[i-1] == '.')
            return 0;
        if(str[i]=='.'&&str[i+1]!='.'&&str[i-1]!='.')//不是连续的，小数点位数加 
        {
            numDian++;
        }
        temp[k] = '\0';
        int num = cinverti(temp);
        if(num < 0 || num >255)
            return 0;
        else
            count++;
    }
    if(count == 4 && numDian == 3)
        return 1;
    else
        return 0;
}

int main()
{
    char ip[100];
    while(cin >> ip)
    {
        int i=0;
        if(IsIP(ip))
        {
            cout << "Y" << endl;
        }
        else
        {
            cout << "N" << endl;
        }
    }
}