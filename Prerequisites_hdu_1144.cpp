#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<iostream>
using namespace std;
int course[100]={0};
int k=0,m=0,c=0,r=0;
int cates[100]={0};
int main()
{
    while(scanf("%d",&k)!=EOF&&k>0)
    {
        int flag=1;//initialize the case is available
        scanf("%d",&m);
        for(int i=0;i<=k-1;i++)
        {
            scanf("%04d",&course[i]);
        }
        for(int i=0;i<=m-1;i++)
        {
            scanf("%d%d",&c,&r);
            int passcnt=0;
            for(int j=0;j<=c-1;j++)
            {
                int degree=0;
                scanf("%d",&degree);
                for(int x=0;x<=k-1;x++)
                {
                    if(course[x]==degree)
                    {
                        passcnt++;
                    }
                }
            }
            if(passcnt<r)
            {
                flag=0;
            }
        }
        if(!flag)
        {
            printf("no\n");
        }
        else
        {
            printf("yes\n");
        }
    }
    return(0);
}
