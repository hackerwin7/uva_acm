#include<stdio.h>
#include<math.h>
#include<stack>
int main()
{
    int n=2,i=0,cases=0;
    for(n=2;cases<=30;n++)
    {
        for(i=2;i<=sqrt(n);i++)
        {
            if(n%i==0) break;
        }
        if(i>sqrt(n)) 
        {
            printf("%d,",n);
            cases++;
        }
    }
    printf("\n");
    return(0);
}
