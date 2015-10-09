/*
Heap get middle
*/
#include<stdio.h>
#include<stdlib.h>
#include<string>
#include<iostream>
using namespace std;
int n=0;//odd number
int num[10000+5]={0};
int heap_fix(int n[],int i,int len)//min heap : fix form up to down
{
    int tmp=n[i];
    int j=i*2+1;//i is father of j,j min child of left and right
    while(j<len)
    {
        if(j+1<len&&n[j+1]<n[j])
        {
            j++;//get the min child
        }
        if(tmp<n[j])
        {
            break;
        }
        n[i]=n[j];
        i=j;
        j=i*2+1;
    }
    n[i]=tmp;
    return(0);
}
int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        for(int i=0;i<=n-1;i++)
        {
            scanf("%d",&num[i]);
        }
        for(int i=(n-1)/2;i>=0;i--)//make up a min heap
        {
            heap_fix(num,i,(n-1)/2+1);//min heap fix up to down
        }
        for(int i=(n-1)/2+1;i<=n-1;i++)
        {
            if(num[i]>num[0])//pass the num[i]<num[0]
            {
                num[0]=num[i];
                heap_fix(num,0,(n-1)/2+1);
            }
        }
        printf("%d\n",num[0]);
    }
    return(0);
}
