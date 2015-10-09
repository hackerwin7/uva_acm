#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<iostream>
using namespace std;
int m=0,n=0;
int map_num[1000+5]={0};//1 is used  0 is not used for opposite
int my_num[100]={0};
int cases=0;
bool comp(int a,int b) {return(a>b);}
int main()
{
    while(scanf("%d%d",&m,&n)!=EOF&&(m+n)>0)
    {
        memset(map_num,0,sizeof(map_num));
        int cnt=0;
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&my_num[i-1]);
            map_num[my_num[i-1]]=1;
        }
        sort(my_num,my_num+n,comp);
        for(int i=0;i<=n-1;i++)
        {
            int j=0;
            for(j=my_num[i]+1;j<=n*m;j++)
            {
                if(!map_num[j])
                {
                    map_num[j]=1;
                    break;
                }
            }
            if(j>n*m) cnt++;
        }
        printf("Case %d: %d\n",++cases,cnt);
    }
    return(0);
}
