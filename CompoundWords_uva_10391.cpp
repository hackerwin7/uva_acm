//
// Created by hp on 4/25/15.
//
#include "stdio.h"
#include "string.h"
#define MM 1000003
char sq [120005][20] = {'\0'};//begin with 1 while(u)
int head[MM] = {0}, next[MM] = {0}, sq_len = 0;
int get_hash(char ss[])
{
    int sum = 0, seed = 13, len = (int)strlen(ss);
    for(int i = 0; i <= len - 1; i++)
        sum = (sum * seed + ss[i]) % MM;
    return sum % MM;
}
void try_to_insert(int s)
{
    int h = get_hash(sq[s]);
    int u = head[h];
    while (u)
    {
        if(strcmp(sq[u], sq[s]) == 0) return;
        u = next[u];
    }
    next[s] = head[h];
    head[h] = s;
}
bool find_word(char ss[])
{
    int h = get_hash(ss);
    int u = head[h];
    while (u)
    {
        if(strcmp(sq[u], ss) == 0) return true;
        u = next[u];
    }
    return false;
}
bool is_compounds(int s)
{
    int len = (int)strlen(sq[s]);
    for(int i = 1; i <= len - 1; i++)//divide
    {
        char s1[20], s2[20];
        strcpy(s1, sq[s]);
        s1[i] = '\0';
        strcpy(s2, sq[s] + i);
        if(find_word(s1) && find_word(s2)) return true;
    }
    return false;
}
int main()
{
    while (scanf("%s", sq[++sq_len]) != EOF)
    {
        if(sq[sq_len][0] == '\0')
        {
            sq_len--;
            continue;
        }
        try_to_insert(sq_len);
    }
    for(int i = 1; i <= sq_len; i++)
    {
        if(is_compounds(i)) printf("%s\n", sq[i]);
    }
    return 0;
}