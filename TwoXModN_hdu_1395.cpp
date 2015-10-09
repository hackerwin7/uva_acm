#include<stdio.h>
#define MM 10000
long long two[MM] = {0};
int x=0,n=0;
int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        int t = 1;
        for(x=1;x<=MM-1;x++)
        {
            t*=2;
            if(t%n==1) break;
            else t=t%n;//sub the number 's range
        }
        if(x<MM) printf("2^%d mod %d = 1\n",x,n);
        else printf("2^? mod %d = 1\n",n);
    }
    return(0);
}
