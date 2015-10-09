#include<stdio.h>
#include<string.h>
int N=0;
bool visited[60001]={false};//begin with 1
int main()
{
    printf("PERFECTION OUTPUT\n");
    while(scanf("%d",&N)!=EOF&&N>0)
    {
        int sum=1;
        memset(visited,false,sizeof(visited));
        for(int i=2;i<=N-1;i++)
        {
            if(visited[i]) break;
            if(N%i==0)
            {
                sum+=i+N/i;
                if(sum>N) break;
                visited[i]=visited[N/i]=true;
            }
        }
        printf("%5d  ",N);
        if(sum>N) printf("ABUNDANT");
        else if(sum<N) printf("DEFICIENT");
        else printf("PERFECT");
        printf("\n");
    }
    printf("END OF OUTPUT\n");
    return(0);
}
