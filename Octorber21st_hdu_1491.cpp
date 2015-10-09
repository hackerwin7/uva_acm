#include<stdio.h>
bool is_leap(int year)
{
    if(year%400==0 || (year%4==0&&(year%100!=0))) return(true);
    else return(false);
}
int month_day[13] = {30,31,28,31,30,31,30,31,31,30,31,30,31};
int t=0;
int m,d;
int cmp_date(int m1,int d1,int m2,int d2)
{
    if(m1>m2) return 1;
    else if(m1<m2) return -1;
    else
    {
        if(d1>d2) return 1;
        else if(d1<d2) return -1;
        else return 0;
    }
}
int get_days(int m1,int d1,int m2,int d2)
{
    int sum=0;
    if(m1<m2)
    {
        sum+=month_day[m1]-d1;
        for(int i=m1+1;i<=m2-1;i++) sum+=month_day[i];
        sum+=d2;
    }
    else if(m1 == m2) sum+=(d2-d1);
    else sum = 0;
    return sum;
}
int main()
{
    while(scanf("%d",&t)!=EOF&&t>0)
    {
        while(t--)
        {
            scanf("%d%d",&m,&d);
            if(cmp_date(m,d,10,21)>0) printf("What a pity, it has passed!\n");
            else if(cmp_date(m,d,10,21)<0) printf("%d\n",get_days(m,d,10,21));
            else printf("It's today!!\n");
        }
    }
    return(0);
}
