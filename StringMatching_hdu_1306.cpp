#include<stdio.h>
#include<string.h>
char str1[50],str2[50];
void swaps(int &a,int &b){int tmp=a;a=b;b=tmp;}
int gcd(int a,int b){if(a<b) swaps(a,b);return(b?gcd(b,a%b):a);}
int main()
{
    while(scanf("%s",str1)!=EOF&&str1[0]!='-')
    {
        scanf("%s",str2);
        int len1=strlen(str1);
        int len2=strlen(str2);
        int max_com=0;
        //str2 is front of the str1, j=end -> j=0  to i=0
        for(int j=len2-1;j>=1;j--)
        {
            int com_char=0;
            for(int i=0,j1=j;j1<=len2-1&&i<=len1-1;i++,j1++)
            {
                if(str1[i]==str2[j1]) com_char++; 
            }
            if(com_char>max_com) max_com=com_char;
        }
        //str2's first char  is same position of str1's
        int com_char=0;
        for(int i=0,j=0;i<=len1-1&&j<=len2-1;i++,j++)
        {
            if(str1[i]==str2[j]) com_char++;
        }
        if(com_char>max_com) max_com=com_char;
        //str2 is behind of the str1, j=0 to i=1 -> i=end
        for(int i=1;i<=len1-1;i++)
        {
            int com_char=0;
            for(int j=0,i1=i;j<=len2-1&&i1<=len1-1;j++,i1++)
            {
                if(str1[i1]==str2[j]) com_char++;
            }
            if(com_char>max_com) max_com=com_char;
        }
        int ups=max_com+max_com;
        int downs=len1+len2;
        int gcd_num=gcd(ups,downs);
        if(ups%downs==0) printf("appx(%s,%s) = %d\n",str1,str2,ups/downs);
        else printf("appx(%s,%s) = %d/%d\n",str1,str2,ups/gcd_num,downs/gcd_num);
    }
    return(0);
}
