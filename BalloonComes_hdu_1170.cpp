#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
char c='\0';
int a=0,b=0;
int T=0;
int main()
{
    scanf("%d",&T);
    getchar();//eat '\n'
    while(T--)
    {
        scanf("%c %d %d",&c,&a,&b);
        getchar();//eat '\n'
        switch(c)
        {
        case '+':
            printf("%d\n",a+b);
            break;
        case '-':
            printf("%d\n",a-b);
            break;
        case '*':
            printf("%d\n",a*b);
            break;
        case '/':
            if(a%b==0)
            {
                printf("%d\n",a/b);
            }
            else
            {
                printf("%.2f\n",(float)a/b);
            }
            break;
        }
    }
    return(0);
}
