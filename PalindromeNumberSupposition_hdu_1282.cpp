#include<stdio.h>
int num=0;
int save[10005];
int reverse_num(int num)
{
    int renum=0;
    while(num>0)
    {
        renum=renum*10+num%10;
        num/=10;
    }
    return(renum);
}
int main()
{
    while(scanf("%d",&num)!=EOF)
    {
        int cnt=0;
        save[cnt++]=num;
        int renum = reverse_num(num);
        while(num!=renum)
        {
            num+=renum;
            save[cnt++]=num;
            renum=reverse_num(num);
        }
        printf("%d\n",cnt-1);
        printf("%d",save[0]);
        for(int i=1;i<=cnt-1;i++) printf("--->%d",save[i]);
        printf("\n");
    }
    return(0);
}
