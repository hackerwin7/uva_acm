#include<stdio.h>
#include<string.h>
bool circle[29]={true};//true is the people is alive,begin withe 1
int ans[14]={0};
int k=0,m=0;
int init()
{
    for(k=1;k<=13;k++)
    {
        int n=k+k;
        for(m=k+1;;m++)
        {
            memset(circle,true,sizeof(circle));
            int start=0,killed=0;
            int flag=0,pre=0;
            while(!flag)
            {
                int step = m % (n - killed) - pre;//last step to alive people
                if(step<0) step=n-killed-pre;
                if(step==0&&pre==0) step=n;
                for(int i=1;i<=step;i++)
                {
                    start = (start + 1) % (n + 1);
                    if(start==0) start=1;
                    if(!circle[start]) i--; 
                }
                circle[start]=false;
                killed++;
                if(start<=k) break;
                if(killed==k)
                {
                    flag=1;
                    break;
                }
                while(!circle[start])//reset step to alive people
                {
                    start = (start + 1) % (n + 1);
                    if(start==0) start=1;
                }
                pre = 1;
            }
            if(flag) break;
        }
        ans[k]=m;
    }
    return(0);
}
int main()
{
    init();
    while(scanf("%d",&k)!=EOF&&k>0) printf("%d\n",ans[k]);
    return(0);
}
