#include<stdio.h>
int nuts=0,peo=0;
int main()
{
    while(scanf("%d",&nuts)!=EOF&&nuts>=0)
    {
        int flag=0;
        for(peo=nuts-1;peo>=2;peo--)
        {
            int sum = nuts,turn = 0;
            for(turn=1;turn<=peo;turn++)
            {
                if((sum-1)%peo!=0) break;
                sum = sum -1 - (sum-1) / peo;
            }
            if((turn > peo)&&(sum%peo == 0)) {flag=1;break;}//have found the max number
        }
        if(flag) printf("%d coconuts, %d people and 1 monkey\n",nuts,peo);
        else printf("%d coconuts, no solution\n",nuts);
    }
    return(0);
}
