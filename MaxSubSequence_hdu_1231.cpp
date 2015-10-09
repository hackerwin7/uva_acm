#include<stdio.h>// max(j)={num[j],max(j-1)+num[j]}
int max_seq[10000+5];
int num[10000+5];
int K=0;
int max_sum=0;
int main()
{
    while(scanf("%d",&K)!=EOF&&K>0)
    {
        for(int i=0;i<=K-1;i++)
        {
            scanf("%d",&num[i]);
        }
        max_sum=max_seq[0]=num[0];
        int start_ind=0,end_ind=0;
        int max_start=0,max_end=0;
        for(int i=1;i<=K-1;i++)
        {
            if(num[i]>max_seq[i-1]+num[i])
            {
                max_seq[i]=num[i];
                start_ind=i;
                end_ind=i;
            }
            else if(num[i]<=max_seq[i-1]+num[i])
            {
                max_seq[i]=max_seq[i-1]+num[i];
                end_ind=i;
            }
            if(max_seq[i]>max_sum)
            {
                max_sum=max_seq[i];
                max_start=start_ind;
                max_end=end_ind;
            }
        }
        printf("%d %d %d\n",max_sum>=0?max_sum:0,max_sum>=0?num[max_start]:num[0],max_sum>=0?num[max_end]:num[K-1]);
    }
    return(0);
}
