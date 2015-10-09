#include<stdio.h>
#include<string.h>
char str1[50],str2[50];
int str1_table[26],str2_table[26];//the index is the uppercase character
void swaps(int &a,int &b){int tmp=a;a=b;b=tmp;}
int gcd(int a, int b) {if(a<b) swaps(a,b);return(b ? gcd(b,a%b) : a);}
int main()
{
    while(scanf("%s",str1)!=EOF&&str1[0]!='-')
    {
        scanf("%s",str2);
        int len1=strlen(str1);
        int len2=strlen(str2);
        memset(str1_table,0,sizeof(str1_table));
        memset(str2_table,0,sizeof(str2_table));
        for(int i=0;i<=len1-1;i++) str1_table[str1[i]-'A']++;
        for(int i=0;i<=len2-1;i++) str2_table[str2[i]-'A']++;
        int common_char=0;
        for(int i=0;i<=25;i++) common_char+=str1_table[i]<str2_table[i]?str1_table[i]:str2_table[i];
        int ups=common_char+common_char;
        int downs=len1+len2;
        int gcd_num=gcd(downs,ups);
        if(ups%downs!=0) printf("appx(%s,%s) = %d/%d\n",str1,str2,ups/gcd_num,downs/gcd_num);
        else printf("appx(%s,%s) = %d\n",str1,str2,ups/downs);
    }
    return(0);
}
