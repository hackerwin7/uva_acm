#include<stdio.h>
#include<math.h>
#define M 10005
bool prime[M];//begin with 1
int num=0;
int main()
{
    //generate prime number
    prime[0]=false;prime[1]=false;prime[2]=true;
    for(int i=3;i<=M-1;i++)
    {
        if(i%2==0) prime[i]=false;
        else prime[i]=true;
    }
    for(int i=3;i<=sqrt(M-1);i++)
    {
        for(int j=i+i;j<=M-1;j+=i) prime[j]=false;
    }
    //get input and process
    while(scanf("%d",&num)!=EOF)
    {
        int mid = num/2;
        while(!prime[mid]||!prime[num-mid]) mid++;
        printf("%d %d\n",num - mid,mid);
    }
    return(0);
}
