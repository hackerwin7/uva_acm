#include<stdio.h>
int o=0,p=0,n=0,d=0;
int main()
{
    while(scanf("%d",&d)!=EOF&&d>0)
    {
        while(d--)
        {
            scanf("%d",&n);
            int bit = 1;
            for(p=0;p<=20;p++)
            {
                if(bit>n) break;
                if(n%bit==0&&(n/bit)%2!=0) break;
                bit*=2;
            }
            o = n / bit;
            printf("%d %d\n",o,p);
        }
    }
    return(0);
}
