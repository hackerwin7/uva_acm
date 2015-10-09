#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<iostream>
using namespace std;
long n=0;
int main()
{
    n=15;
    for(long i=1;i<=n;i++)
    {
        long num=(long)pow(i,i);
        printf("%ld:\n",num);
        while(num>=10)
        {
            long sum=0;
            while(num>0)
            {
                sum+=num%10;
                num/=10;
            }
            num=sum;
        }
        printf("%ld\n",num);
    }
    return(0);
}
