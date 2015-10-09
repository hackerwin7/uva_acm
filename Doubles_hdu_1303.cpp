#include<stdio.h>
#include<string.h>
#define M 100
bool num[300];
int n=0;
int cnt=0;
int main()
{
    memset(num,false,sizeof(num));
    while(scanf("%d",&n)!=EOF&&n>=0)
    {
        if(n>0)
        {
            num[n]=true;
        }
        else//n==0
        {
            for(int i=1;i<=M;i++)
            {
                if(num[i]&&num[2*i])    cnt++;
            }
            printf("%d\n",cnt);
            memset(num,false,sizeof(num));
            cnt=0;
        }
    }
    return(0);
}
