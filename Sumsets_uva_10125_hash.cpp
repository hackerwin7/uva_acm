//
// Created by hp on 7/31/15.
//
#include<stdio.h>
#include "string.h"
#define MM 1000003
#define MIN -536870912
typedef struct node
{
    long a;
    long b;
    node()
    {
        a = b = 0;
    }
}node;
node nst[MM];//save (a, b) node array
long st[MM] = {0}, s[MM] = {0};//st : sum for a + b ; s : for n numbers
int st_len_1 = 0, n = 0, nst_len_1 = 0;
int head[MM] = {0}, next[MM] = {0};
long maxd = 0;// save the n numbers
int hash(long num)
{
    return (int)(num % MM);
}
int try_to_insert(int s)
{
    int h = hash(st[s]);
    int u = head[h];
    while (u)
    {
        if(st[u] == st[s]) return 1; //exist data
        else u = next[u];
    }
    next[s] = head[h];
    head[h] = s;
    return 0;
}
int is_exist(long d, long c)
{
    long val = d - c;
    int h = hash(val);
    int u = head[h];
    while (u)
    {
        if(st[u] == val && d != nst[u].a && d != nst[u].b && c != nst[u].a && c != nst[u].b) return 1;
        else u = next[u];
    }
    return 0;
}
int main()
{
    while (scanf("%d", &n) != EOF && n > 0)
    {
        st_len_1 = nst_len_1 = 1;//begin with 1 , 0 is init value for head[] and next[]
        maxd = MIN;
        memset(st, 0, sizeof(st));
        memset(head, 0, sizeof(head));
        memset(next, 0, sizeof(next));
        for(int i = 0; i <= n - 1; i++) scanf("%ld", &s[i]);
        for(int i = 0; i <= n - 1; i++) // a+b is no need to worry the sort
            for(int j = i + 1; j <= n - 1; j++)
            {
                long sum = s[i] + s[j];// a+b
                st[st_len_1++] = sum;
                nst[nst_len_1].a = s[i];
                nst[nst_len_1].b = s[j];
                nst_len_1++;
                try_to_insert(st_len_1 - 1);
            }
        for(int i = 0; i <= n - 1; i++)// d-c have is sortable
            for(int j = 0; j <= n-1; j++)
            {
                if(s[i] != s[j])
                {
                    long div = s[i] - s[j];// d-c
                    if(is_exist(s[i], s[j]) && s[i] > maxd)
                        maxd = s[i];
                }
            }
        if(maxd == MIN)
            printf("no solution\n");
        else
            printf("%ld\n", maxd);
    }
    return 0;
}
