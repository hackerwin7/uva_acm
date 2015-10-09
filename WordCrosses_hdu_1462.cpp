#include<stdio.h>
#include<string.h>
char s1[12],s2[12],s3[12],s4[12];
int l1,l2,l3,l4;
int f1,f2,f3,f4;//the first letter 's position in the global coordinate
int c1,c2,c3,c4;//the common letter 's position in own string
int hlen=3, vlen, ilen;//number of spaces, initialize length of spaces for first column
int print_space(int num)
{
    for(int i=0;i<=num-1;i++) printf(" ");
    return(0);
}
int main()
{
    int cases = 0;
    while(scanf("%s",s1)!=EOF&&s1[0]!='#')
    {
        if(cases > 0) printf("\n");
        int i,j;
        int line=0;//the length of coordinate
        scanf("%s%s%s",s2,s3,s4);
        l1=strlen(s1);
        l2=strlen(s2);
        l3=strlen(s3);
        l4=strlen(s4);
        int flag1=0;//can not print result
        for(i=0;i<=l1-1;i++)
        {
            for(j=0;j<=l2-1;j++)
            {
                if(s1[i] == s2[j])
                {
                    c1=i;
                    c2=j;
                    flag1=1;
                    break;
                }
            }
            if(j<=l2-1) 
            {
                break;
            }
        }
        int flag2=0;
        for(i=0;i<=l3-1;i++)
        {
            for(j=0;j<=l4-1;j++)
            {
                if(s3[i] == s4[j])
                {
                    c3=i;
                    c4=j;
                    flag2=1;
                    break;
                }
            }
            if(j<=l4-1) 
            {
                break;
            }
        }
        if(flag1==1&&flag2==1)
        {
            if(c2 > c4)//f2=0
            {
                f1=c2;
                f2=0;
                f3=f1;
                f4=f3-c4;   
                line = f4+l4-1 > l2-1 ? f4+l4-1 : l2-1;
            }
            else
            {
                f4=0;
                f1=c4;
                f3=f1;
                f2=f3-c2;
                line = f2+l2-1 > l4-1 ? f2+l2-1 : l4-1;
            }
            vlen=l1-1-c1 + 3 + c3;
            ilen=c1;
            for(i=0;i<=line;i++)
            {
                if(i!=f1)
                {
                    print_space(ilen);
                    if(i>=f2&&(i-f2)<=l2-1) printf("%c",s2[i-f2]);
                    else printf(" ");
                }
                if(i!=f1)
                {
                    if(i>=f4&&(i-f4)<=l4-1) print_space(vlen);//PE
                    if(i>=f4&&(i-f4)<=l4-1) printf("%c",s4[i-f4]);
                    //else printf(" ");//PE
                }
                if(i==f1)
                {
                    printf("%s",s1);
                    print_space(hlen);
                    printf("%s",s3);
                }
                printf("\n");
            }
        }
        else//print no answer
        {
            printf("Unable to make two crosses\n");
        }
        cases++;
    }
    return(0);
}
