#include<stdio.h>
int min_time[2005];//begin with index 1
int K=0,N=0;
int S[2005],D[2005];
int main()
{
    while(scanf("%d",&N)!=EOF)
    {
        while(N--)
        {
            scanf("%d",&K);
            for(int i=1;i<=K;i++) scanf("%d",&S[i]);
            for(int i=1;i<=K-1;i++) scanf("%d",&D[i]);
            min_time[0]=0;
            min_time[1]=S[1];
            for(int i=2;i<=K;i++) min_time[i] = min_time[i-1]+S[i] < min_time[i-2]+D[i-1] ?
                min_time[i-1]+S[i] : min_time[i-2]+D[i-1];
            int second = min_time[K] % 60;
            int minute = (min_time[K]/60) %60;
            int hour = (min_time[K]/60/60) % 24;
            hour = hour > 12 ? hour -12 : hour;//time print is bug
            printf("%02d:%02d:%02d ",hour+8,minute,second);
            if(min_time[K]+8*3600 >= 12*3600) printf("pm\n");
            else printf("am\n");
        }
    }
    return(0);
}
