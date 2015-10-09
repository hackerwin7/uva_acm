#include<stdio.h>
#include<string.h>
#include<ctype.h>
int n=0;
char nstr[20];
int reverse_str(char str[])
{
    int i=0;
    int j=strlen(str)-1;
    while(i<j)
    {
        char tmp=str[i];
        str[i]=str[j];
        str[j]=tmp;
        i++;
        j--;
    }
    return(0);
}
int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        while(n--)
        {
            scanf("%s",nstr);
            int len=strlen(nstr);
            int i=len-1;
            while(i>=0&&nstr[i]=='0')
            {
                nstr[i]='+';
                i--;
            }
            int endz=i+1;
            int k=0;
            char num[20];
            i=0;
            while(i<=len-1)
            {
                if(isdigit(nstr[i]))    num[k++]=nstr[i];
                i++;
            }
            num[k]='\0';
            reverse_str(num);
            if(nstr[0]=='-')    printf("%c%s",nstr[0],num);
            else printf("%s",num);
            for(int i=endz;i<=len-1;i++) printf("0");
            printf("\n");
        }
    }
    return(0);
}
