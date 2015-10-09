#include<stdio.h>
int N=0;
int num=0;
int main()
{
    while(scanf("%d",&N)!=EOF)
    {
        while(N--)
        {
            scanf("%d",&num);
            int print_num=0;
            while(num>1)
            {
                if(num%2==1) {printf("%d",num);print_num++;num = num * 3 + 1;break;}
                else    num = num /2;
            }
            while(num>1)
            {
                if(num%2==1) {printf(" %d",num);print_num++;num = num * 3 + 1;}
                else    num = num /2;
            }   
            if(print_num == 0) printf("No number can be output !");
            printf("\n");
        }
    }
    return(0);
}
