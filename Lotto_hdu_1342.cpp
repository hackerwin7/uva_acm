#include<stdio.h>
int k=0,cases=0;//length
int S[20],sub[10];
//dfs the S array
int  DFS(int S_cur,int sub_cur)
{
    if(sub_cur>=6)
    {
        printf("%d",sub[0]);
        for(int i=1;i<=6-1;i++) printf(" %d",sub[i]);
        printf("\n");
    }
    else
    {
        if(S_cur>=k) return(0);
        sub[sub_cur]=S[S_cur];
        DFS(S_cur+1,sub_cur+1);//selected elem into sub
        DFS(S_cur+1,sub_cur);//not selected
    }
    return(0);
}
int main()
{
    while(scanf("%d",&k)!=EOF&&k>0)
    {
        if(cases++) printf("\n");
        for(int i=0;i<=k-1;i++) scanf("%d",&S[i]);
        DFS(0,0);//dfs the S array to select element into sub array
    }
    return(0);
}
