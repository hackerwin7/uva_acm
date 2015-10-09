//
// Created by hp on 8/13/15.
//
#include "stdio.h"
#include "string.h"
#define LL 1505
#define CL 15
#define MM 2250005
char lan1[LL][CL] = {'\0'}, lan2[LL][CL] = {'\0'};
int M = 0, N = 0, T = 0, sl = 0;
char st[MM][CL + CL] = {'\0'};
int head[MM] = {0}, next[MM] = {0};//init value is 0, index will be begin from 1
int catlang(char sum[], char s1[], char s2[])
{
    int sl1 = (int)strlen(s1);
    strcpy(sum, s1);
    strcpy(sum + sl1, s2);
    return 0;
}
int hash(char str[])
{
    int sl = (int)strlen(str);
    int seed = 131;
    int sum = 0;
    for(int i = 0; i <= sl - 1; i++)
        sum = (sum * seed + str[i]) % MM;
    return sum % MM;
}
int try_to_insert(int s)
{
    int h = hash(st[s]);
    int u = head[h];
    while (u)
    {
        if(strcmp(st[u], st[s]) == 0) return 0;// had been existed, do not insert
        else u = next[u];
    }
    next[s] = head[h];
    head[h] = s;
    return 1;// not existed ,  insert it
}
int main()
{
    while (scanf("%d", &T) != EOF && T > 0)
    {
        for(int cases = 1; cases <= T; cases++)
        {
            memset(head, 0, sizeof(head));
            memset(next, 0, sizeof(next));
            sl = 1;//begin with 1, 0 is init for head and next
            int sum = 0;
            scanf("%d%d", &M, &N);
            getchar();//eat '\n' after scanf M N
            for(int i = 0; i <= M - 1; i++)
            {
                fgets(lan1[i], CL, stdin);
                lan1[i][strlen(lan1[i]) - 1] = '\0';//if(lan1[i][0] == '\0') lan1[i][0] = ' ';// " " replace the "", in order to hash it  , error  " a" == "a "
            }
            for(int i = 0; i <= N - 1; i++)
            {
                fgets(lan2[i], CL, stdin);
                lan2[i][strlen(lan2[i]) - 1] = '\0';//if(lan2[i][0] == '\0') lan2[i][0] = ' ';
            }
            for(int i = 0; i <= M - 1; i++)
                for(int j = 0; j <= N - 1; j++)
                {
                    char cats[CL + CL] = {'\0'};
                    catlang(cats, lan1[i], lan2[j]);
                    strcpy(st[sl++], cats);
                    if(try_to_insert(sl - 1))
                        sum++;
                }
            printf("Case %d: %d\n", cases, sum);
        }
    }
    return 0;
}
