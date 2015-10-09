#include<stdio.h>
int H=0,U=0,D=0,F=0;
int main()
{
    while(scanf("%d%d%d%d",&H,&U,&D,&F)!=EOF&&H>0)
    {
        double pre_h=0,cli_d=0,aft_h=0,nigh_h=0;
        int day=0;
        double max_h=0,min_h=0;
        while(max_h<=H&&min_h>=0)//if all not demand the condition we use continue to let only one can not demand the condition
        {
            day++;
            pre_h=nigh_h;
            cli_d=U-U*(F/100.0)*(day-1);
            if(cli_d<0) cli_d=0;
            aft_h=pre_h+cli_d;
            if(aft_h>(double)H) {max_h=aft_h;break;}
            nigh_h=aft_h-D;
            if(nigh_h<0.0) {min_h=nigh_h;break;}
        }
        if(max_h>(double)H) printf("success on day %d\n",day);
        else printf("failure on day %d\n",day);
    }
    return(0);
}
