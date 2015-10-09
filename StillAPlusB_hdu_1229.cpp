#include<stdio.h>
int A=0,B=0,K=0;
int main()
{
    while(scanf("%d%d%d",&A,&B,&K)!=EOF&&(A+B)!=0)
    {
        int temp=A+B;
        int C=-1;
        int i=0;
        for(i=1;i<=K;i++)
        {
            if((A%10)!=(B%10))
            {
                C=temp;
                break;
            }
            A/=10;
            B/=10;
            if(A==0&&B==0) break;//WA
        }
        printf("%d\n",C);
    }
    return(0);
}
