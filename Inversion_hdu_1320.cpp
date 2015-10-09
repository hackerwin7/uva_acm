#include<stdio.h>
int p_arr[50+5],i_arr[50+5];
int N=0;
char kind='\0';
int main()
{
    while(scanf("%d",&N)!=EOF&&N>0)
    {
        for(int i=0;i<=50+5-1;i++) {p_arr[i]=i_arr[i]=1000;}
        scanf("%c",&kind);
        while(!(kind=='P'||kind=='I')) scanf("%c",&kind);
        if(kind=='I')
        {
            for(int i=0;i<=N-1;i++)
            {
                scanf("%d",&i_arr[i]);
                int bigger_cnt = 0;
                int p_ind=0;
                while(bigger_cnt < i_arr[i]&&p_ind<=N-1)
                {
                    if(p_arr[p_ind]>i+1) bigger_cnt++;
                    p_ind++;
                }
                while(p_arr[p_ind]<=N&&p_ind<=N-1) p_ind++;//it must be not visited
                p_arr[p_ind]=i+1;
            }
            printf("%d",p_arr[0]);
            for(int i=1;i<=N-1;i++) printf(" %d",p_arr[i]);
        }
        else
        {
            for(int i=0;i<=N-1;i++) scanf("%d",&p_arr[i]);
            for(int i=1;i<=N;i++)
            {
                int j=0,bigger_cnt=0;
                while(p_arr[j]!=i&&j<=N-1)
                {
                    if(p_arr[j]>i) bigger_cnt++;
                    j++;
                }
                i_arr[i-1]=bigger_cnt;
            }
            printf("%d",i_arr[0]);
            for(int i=1;i<=N-1;i++) printf(" %d",i_arr[i]);
        }
        printf("\n");
    }
    return(0);
}
