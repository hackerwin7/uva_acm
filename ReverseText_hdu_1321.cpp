#include<stdio.h>
#include<string.h>
int N=0;
char in_str[100];
int main()
{
    while(scanf("%d",&N)!=EOF&&N>0)
    {
        while(N--)
        {
            fgets(in_str,100,stdin);
            while(in_str[0]=='\n') fgets(in_str,100,stdin);
            in_str[strlen(in_str)-1] = '\0';
            int len=strlen(in_str);
            for(int i=len-1;i>=0;i--) printf("%c",in_str[i]);
            printf("\n");
        }
    }
    return(0);
}
