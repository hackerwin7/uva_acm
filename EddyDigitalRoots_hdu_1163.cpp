#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
using namespace std;
int root[10000+5];//n's root ,begin with 1
int root_n[10000+5];//n^n's root,begin with 1
int n=0;
int get_root(int n)
{
    int sum=0;
    while(n>=10)
    {
        sum=0;
        while(n>0)
        {
            sum+=n%10;
            n/=10;
        }
        n=sum;
    }
    return(n);
}
int main()
{
    for(int i=1;i<=10000;i++)
    {
        root[i]=get_root(i);
        int cumula=root[i];//cumulation
        for(int k=1;k<=i-1;k++)
        {
            cumula*=root[i];
            cumula=get_root(cumula);
        }
        root_n[i]=cumula;
    }
    while(scanf("%d",&n)!=EOF&&n>0)
    {
        printf("%d\n",root_n[n]);
    }
    return(0);
}
