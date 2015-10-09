#include<stdio.h>
#include<string.h>
bool sol[5000+5];//begin with 1
int N=0;
int sol_cnt=0;
int simulate(int interval)
{
    int sub_num=0,ind=0;
    for(int i=1;i<=sol_cnt;i++)
    {
        if(sol[i]) ind++;
        if(ind == interval)
        {
            ind = 0;
            sol[i] = false;
            sub_num++;
        }
    }
    return(sub_num);
}
int main()
{
    while(scanf("%d",&N)!=EOF)
    {
        while(N--)
        {
            memset(sol,true,sizeof(sol));
            scanf("%d",&sol_cnt);
            int sum = sol_cnt;
            while(sum>3)
            {
                //interval 2
                sum-=simulate(2);
                if(sum<=3) break;
                //interval 3
                sum-=simulate(3);
                if(sum<=3) break;
            }
            int i=0;
            for(i=1;i<=sol_cnt;i++) if(sol[i]) {printf("%d",i);break;}
            for(i=i+1;i<=sol_cnt;i++) if(sol[i]) printf(" %d",i);
            printf("\n");
        }
    }
    return(0);
}
