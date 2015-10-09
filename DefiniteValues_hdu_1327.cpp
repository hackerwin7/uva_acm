#include<stdio.h>
#include<string.h>
int map_chars[300];//map['a'] = 1 is definite and 0 is indefinite
int n=0,cases=0;
char in_str[10];
int main()
{
    while(scanf("%d",&n)!=EOF&&n>0)
    {
        printf("Program #%d\n",++cases);
        memset(map_chars,0,sizeof(map_chars));
        map_chars['a']=1;
        for(int i=1;i<=n;i++)
        {
            fgets(in_str,10,stdin);
            while(in_str[0]=='\n') fgets(in_str,10,stdin);
            map_chars[in_str[0]]=map_chars[in_str[4]];
        }
        int flag=0,i=0;
        for(i='a';i<='z';i++)
        {
            if(map_chars[i]>0)
            {
                flag=1;
                printf("%c ",i);
            }
        }
        if(!flag) printf("none");
        printf("\n\n");
    }
    return(0);
}
