#include<stdio.h>
int x=0,y=0,z=0,n=0;
int calc()
{
    for(x=1;x*x<=n/3;x++)
        for(y=x;y*y<=n;y++)
            for(z=y;z*z<=n;z++)
                if(x*x+y*y+z*z == n) return(0);
    return(0);
}
int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        calc();
        printf("%d %d %d\n",x,y,z);
    }
    return(0);
}
