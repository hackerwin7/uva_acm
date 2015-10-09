#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
#include<algorithm>
using namespace std;
int num[10000+5]={0};
int n=0;
int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        for(int i=0;i<=n-1;i++)
        {
            scanf("%d",&num[i]);
        }
        sort(num,num+n);
        printf("%d\n",num[n/2]);
    }
    return(0);
}
