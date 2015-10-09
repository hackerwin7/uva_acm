#include<stdio.h>
int s=0,d=0;
int a=0,b=0;
int T=0;
int main()
{
    while(scanf("%d",&T)!=EOF)
    {
        while(T--)
        {
            scanf("%d%d",&s,&d);
            if((s+d)%2!=0||s-d<0||(s-d)%2!=0)
            {
                printf("impossible\n");
            }
            else
            {
                a=(s+d)/2;
                b=(s-d)/2;
                printf("%d %d\n",a,b);
            }
        }
    }
    return(0);
}
