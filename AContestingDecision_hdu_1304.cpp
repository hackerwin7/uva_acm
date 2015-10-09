#include<stdio.h>
#include<string.h>
char in_name[20],max_name[20];
int in_solve=0,max_solve=0;
int in_penal=0,max_penal=0;
int N=0;
int main()
{
    int sub_num=0,sub_time=0;
    while(scanf("%d",&N)!=EOF&&N>0)
    {
        max_solve=0;
        max_penal=0;
        while(N--)
        {
            in_solve=0;
            in_penal=0;
            scanf("%s",in_name);
            for(int i=1;i<=4;i++)
            {
                scanf("%d%d",&sub_num,&sub_time);
                if(sub_num>0&&sub_time>0)   {in_solve++;in_penal+=sub_time + (sub_num-1)*20;}
            }
            if(in_solve>max_solve)  {strcpy(max_name,in_name);max_solve=in_solve;max_penal=in_penal;}
            else if((in_solve==max_solve)&&in_penal<max_penal) {strcpy(max_name,in_name);max_solve=in_solve;max_penal=in_penal;}
        }
        printf("%s %d %d\n",max_name,max_solve,max_penal);
    }
    return(0);
}
