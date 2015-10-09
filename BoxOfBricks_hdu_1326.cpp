#include<stdio.h>
int cases = 0;
int n=0,h=0;
int hs[100];
int main()
{
    while(scanf("%d",&n)!=EOF&&n>0)
    {
        int sum=0,avg=0,mv=0;
        for(int i=0;i<=n-1;i++)
        {
            scanf("%d",&hs[i]);
            sum+=hs[i];
        }
        avg=sum/n;
        for(int i=0;i<=n-1;i++) {if(hs[i]<avg) mv+=avg-hs[i];}
        printf("Set #%d\nThe minimum number of moves is %d.\n\n",++cases,mv); 
    }
    return(0);
}
