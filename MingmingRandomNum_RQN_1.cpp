#include<stdio.h>
#include<string.h>
int ind_value[1005]={0};
int N=0;//the number of the input 
int C=0;//the number of the output
int main()
{
    while(scanf("%d",&N)!=EOF)
    {
        memset(ind_value,0,sizeof(ind_value));
        C=0;
        for(int i=0;i<=N-1;i++)
        {
            int num=0;
            scanf("%d",&num);
            ind_value[num]++;
            if(ind_value[num]==1) C++;
        }
        printf("%d\n",C);
        int i=0;
        for(i=0;i<=1005-1;i++)
        {
            if(ind_value[i]>0) {printf("%d",i);break;}
        }
        for(i=i+1;i<=1005-1;i++)
        {
            if(ind_value[i]>0) {printf(" %d",i);}
        }
        printf("\n");
    }
    return(0);
}
