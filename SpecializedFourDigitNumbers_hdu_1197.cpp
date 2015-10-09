#include<stdio.h>
int digit(int num,int bit)
{
    int sum=0;
    while(num>0)
    {
        sum+=num%bit;
        num/=bit;
    }
    return(sum);
}
int main()
{
    for(int i=2992;i<=9999;i++)
    {
        int dec=digit(i,10);
        int duo=digit(i,12);
        int hex=digit(i,16);
        if(dec==duo&&duo==hex)
        {
            printf("%d\n",i);
        }
    }
    return(0);
}
