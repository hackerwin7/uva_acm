#include<stdio.h>
#include<string.h>
int n=0,cases=0;
char in_str[100];
int main()
{
    while(scanf("%d",&n)!=EOF&&n>0)
    {
        while(n--)
        {
            printf("String #%d\n",++cases);
            scanf("%s",in_str);
            int len=strlen(in_str);
            for(int i=0;i<=len-1;i++) in_str[i]=(in_str[i]-'A'+1)%26+'A';
            printf("%s\n\n",in_str);
        }
    }
    return(0);
}
