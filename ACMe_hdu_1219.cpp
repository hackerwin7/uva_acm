#include<stdio.h>
#include<ctype.h>
#include<string.h>
#define GET_INDEX(x) x-'a'
#define GET_CHAR(x) x+'a'
int type_list[26];
char str[100000+5];//article
int main()
{
    while(fgets(str,100005,stdin))
    {
        memset(type_list,0,sizeof(type_list));
        int len=strlen(str);
        str[len-1]='\0';//this is '\n'
        len=len-1;
        for(int i=0;i<=len-1;i++)
        {
            if(islower(str[i]))
            {
                type_list[GET_INDEX(str[i])]++;
            }
        }
        for(int i=0;i<=26-1;i++)
        {
            printf("%c:%d\n",GET_CHAR(i),type_list[i]);
        }
        printf("\n");
    }
    return(0);
}
