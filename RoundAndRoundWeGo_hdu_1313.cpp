#include<stdio.h>
#include<string.h>
char in_str[200];
bool is_cyclic(char str[])
{
    int len = strlen(str);
    for(int i=1;i<=6;i++)
    {
        char out_str[200];
        int carry = 0;
        for(int j=len-1;j>=0;j--)
        {
            int result = (in_str[j] - '0') * i + carry;
            int bit_val = result % 10;
            carry = result / 10;
            out_str[j] = bit_val + '0';
        }
        out_str[len]='\0';
        for(int j=0,k=len;j<=len-1;j++,k++) out_str[k] = out_str[j];
        out_str[len+len-1]='\0';
        if(strstr(out_str,in_str)==NULL) return(false);
    }
    return(true);
}
int main()
{
    while(scanf("%s",in_str)!=EOF)
    {
        if(is_cyclic(in_str)) printf("%s is cyclic\n",in_str);
        else printf("%s is not cyclic\n",in_str);
    }
    return(0);
}
