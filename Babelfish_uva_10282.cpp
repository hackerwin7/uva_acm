//
// Created by hp on 15-4-8.
//
#include "stdio.h"
#include "string.h"
#define MM 100003
char en_dic[MM][15];
char wl_dic[MM][15];
int head[MM], next[MM];//save the index of char array
int en_len = 0, wl_len = 0, space_flag = 0;
char in_str[100];
bool has_space(char str[])
{
    int len = (int)strlen(str);
    for(int i = 0; i <= len - 1; i++)
        if(str[i] == ' ')
            return true;
    return false;
}
int extract_word(char str[], char s1[], char s2[])
{
    int i = 0, i1 = 0, i2 = 0, len = (int)strlen(str);
    for(i = 0; i <= len - 1 && str[i] != ' '; i++)
        s1[i1++] = in_str[i];
    s1[i1] = '\0';
    for(i = i + 1; i <= len - 1; i++)
        s2[i2++] = in_str[i];
    s2[i2] = '\0';
    return 0;
}
int get_hash(char str[])
{
    int sum = 0, seed = 131, len = (int)strlen(str);
    for(int i = 0; i <= len - 1; i++)
        sum = (sum * seed + str[i]) % MM;
    return sum % MM;
}
int try_to_insert(int s)
{
    int h = get_hash(wl_dic[s]);
    int u = head[h];
    while (u)//index must begin with 1
    {
        if(strcmp(wl_dic[s], wl_dic[u]) == 0) return 0;//repeated
        u = next[u];
    }
    next[s] = head[h];
    head[h] = s;
    return 1;
}
int find_map(char str[])
{
    int h = get_hash(str);
    int u = head[h];
    while (u)
    {
        if(strcmp(wl_dic[u], str) == 0) return u;
        u = next[u];
    }
    return -1;
}
int main()
{
    memset(head, 0, sizeof(head));
    memset(next, 0, sizeof(next));
    wl_len = en_len = 1;
    while (fgets(in_str, 100, stdin) != NULL)
    {
        if(in_str[0] == '\n') continue;
        if(in_str[strlen(in_str) - 1] == '\n') in_str[strlen(in_str) - 1] = '\0';
        if(space_flag == 0 && has_space(in_str))
        {
            char en_str[10], wl_str[10];
            extract_word(in_str, en_str, wl_str);
            memmove(en_dic[en_len++], en_str, sizeof(en_str));
            memmove(wl_dic[wl_len++], wl_str, sizeof(wl_str));
            try_to_insert(wl_len - 1);
        }
        else
        {
            space_flag = 1;
            int ind = find_map(in_str);
            if(ind >= 1) printf("%s\n", en_dic[ind]);
            else printf("eh\n");
        }
    }
    return 0;
}