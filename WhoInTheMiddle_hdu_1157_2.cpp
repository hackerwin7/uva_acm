/*
divide and conquer, odd number sequence
*/
#include<stdio.h>
#include<stdlib.h>
#include<ctime>
int n=0;//the length of numbers
int num[10000+5]={0};
int partitions(int * n,int len)
{
    srand(time(NULL));
    int k=rand()%len;
    int tmp=n[k];
    n[k]=n[0];
    n[0]=tmp;//swap the divide number to the begin
    int i=0,j=len-1;
    while(i<j)
    {
        while(i<j&&n[j]>tmp)
        {
            j--;
        }
        n[i]=n[j];
        while(i<j&&n[i]<tmp)
        {
            i++;
        }
        n[j]=n[i];
    }
    n[i]=tmp;
    return(i);
}
int quik_divide(int * n,int len,int mid_index)
{
    if(len==1)
    {
        return(n[0]);
    }
    int divide_index=partitions(n,len);
    if(divide_index<mid_index)//give up the left,and update mid_index and length 
    {
        return(quik_divide(n+divide_index+1,len-divide_index-1,mid_index-divide_index-1));
    }
    else if(divide_index>mid_index)//give up the right, and update mid_index and length
    {
        return(quik_divide(n,divide_index,mid_index));
    }
    else//divide-index == mid_index
    {
        return(n[divide_index]);
    }
}
int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        for(int i=0;i<=n-1;i++)
        {
            scanf("%d",&num[i]);
        }
        int mid=quik_divide(num,n,(n-1)/2);
        printf("%d\n",mid);
    }
    return(0);
}
