#include<stdio.h>
#include<math.h>
int N=0;
int main()
{
    while(scanf("%d",&N)!=EOF&&N>0)
    {
        double val=1.0*N*(N+1)*(N+2)/6;
        int bit=(int)log10(val);
        printf("%.2lfE%d\n",val/pow(10.0,bit),bit);
    }
    return(0);
}
