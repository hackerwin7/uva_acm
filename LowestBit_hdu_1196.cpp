#include<stdio.h>
int a=0;
int main()
{
    while(scanf("%d",&a)!=EOF&&a>0)
    {
        int n=0;//the bit
        while(a%2==0)
        {
            n++;
            a/=2;
        }
        printf("%d\n",1<<n);
    }
    return(0);
}
