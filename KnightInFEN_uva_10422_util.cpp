#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#define MM 100
int main()
{
    char ss[5][5];
    int n1=24,n2=24,n3=1;
    int t = MM;
    printf("%d\n",t);
    while(t--)
    {
        int m1=0,m2=0,m3=0;
        for(int i=0;i<=25-1;i++)
        {
            int rand_int = rand()%3;//0  1 2(' ')
            if(rand_int == 2)
            {
                if(m3 < n3)
                {
                    printf(" ");
                    m3++;
                }
                else
                {
                    i--;
                    continue;
                }
            }
            else
            {
                if(rand_int == 1)
                {
                    if(m2 < n2)
                    {
                        printf("%d",rand_int);
                        m2++;
                    }
                    else
                    {
                        i--;
                        continue;
                    }
                }
                else
                {
                    if(m1 < n1)
                    {
                        printf("%d",rand_int);
                        m1++;
                    }
                    else
                    {
                        i--;
                        continue;
                    }
                }
            }
            if(i==4||i==9||i==14||i==19||i==24)
                printf("\n");
        }
        
    }
    return 0;
}