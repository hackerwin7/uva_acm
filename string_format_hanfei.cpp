//
// Created by hp on 8/4/15.
// format the string for hanfei
//
#include<stdio.h>
#include<string.h>
#include "ctype.h"
char cs[3] = {'d', 'M', 'y'};// date and time format
bool is_cs[3] = {false};
char instr[100] = {'\0'};
char ys[10], Ms[10], ds[10], Hs[10], ms[10];
bool flag = false;
int format(char es[], int step)
{
    switch(step)
    {
        case 0:
            strcpy(ds, es);
            break;
        case 1:
            strcpy(Ms, es);
            break;
        case 2:
            strcpy(ys, es);
            break;
    }
    is_cs[step] = true;
    return 1;
}
int unformat(char es[], int step)
{
    switch(step)
    {
        case 0:
            memset(ds, '\0', sizeof(ms));
            break;
        case 1:
            memset(Ms, '\0', sizeof(ms));
            break;
        case 2:
            memset(ys, '\0', sizeof(ms));
            break;
    }
    is_cs[step] = false;
    return 1;
}
int DFS(char s[], int step, int cur)
{
    if(step >= strlen(cs))
    {
        if(strlen(ys) == 4)
            flag = true;
        return 0;
    }
    if(cur < 0) //back track
        return 0;
    if(step == 0)
    {
        for(int c = step; c <= strlen(cs) - 1; c++) //dfs and back trace
        {
            char es[10] = {0};
            int i = 0, j = 0, e = 0;
            for(i = cur; i >= 0; i--)
            {
                if(isdigit(s[i]))
                {
                    if(c != (strlen(cs) - 1))
                    {
                        for(j = i - 1; j <= i; j++)// 2 bits
                            es[e++] = s[j];
                        es[e] = '\0';
                    }
                    else
                    {
                        for(j = i - 3; j <= i; j++)// 2 bits
                        {
                            if(j < 0) break;
                            es[e++] = s[j];
                        }
                        es[e] = '\0';
                    }
                    break;
                }
            }
            int next_cur = i - 2;
            format(es, c);
            DFS(s, c + 1, next_cur);//dfs next step
            if(flag) return 0;
            unformat(es, c);
        }
    }
    else
    {
        char es[10] = {0};
        int i = 0, j = 0, e = 0;
        for(i = cur; i >= 0; i--)
        {
            if(isdigit(s[i]))
            {
                if(step != (strlen(cs) - 1))
                {
                    for(j = i - 1; j <= i; j++)// 2 bits
                        es[e++] = s[j];
                    es[e] = '\0';
                }
                else
                {
                    for(j = i - 3; j <= i; j++)// 2 bits
                    {
                        if(j < 0) break;
                        es[e++] = s[j];
                    }
                    es[e] = '\0';
                }
                break;
            }
        }
        int next_cur = i - 2;
        format(es, step);
        DFS(s, step + 1, next_cur);//dfs next step
        if(flag) return 0;
        unformat(es, step);
    }
    return 0;
}
int printEle()
{
    printf("mm : %s\n", ms);
    printf("HH : %s\n", Hs);
    printf("dd : %s\n", ds);
    printf("MM : %s\n", Ms);
    printf("YY : %s\n", ys);
    printf("\n");
}
int predeal(char s[])
{
    int sl = (int)strlen(s);
    int i = 0, j = 0, k = 0;
    int mi = 0, hi = 0;
    int next = sl - 1;
    for(i = sl - 1; i >= 0; i--)
        if(s[i] == ':') break;
    if(i >= 0)//exists ':'
    {
        for(j = i + 1; j <= sl -1; j++)// minutes
            if(isdigit(s[j]))
            {
                for(int jj = j; jj <= sl - 1 && isdigit(s[jj]); jj++)
                    ms[mi++] = s[jj];
                break;
            }
            else if(s[j] == ' ') continue;
            else break;
        for(j = i - 1; j >= 0; j--)// hours
        {
            if(isdigit(s[j]))
            {
                if(isdigit(s[j - 1]))
                {
                    Hs[0] = s[j - 1];
                    Hs[1] = s[j];
                    next = j - 2;
                }
                else
                {
                    Hs[0] = s[j];
                    next = j - 1;
                }
                break;
            }
            else if(s[j] == ' ') continue;
            else break;
        }

    }
    return next;
}
int main()
{
    while (fgets(instr, sizeof(instr), stdin) != NULL)
    {
        if(instr[0] == '\n') continue;
        instr[strlen(instr) - 1] = '\0';
        flag = false;
        memset(ms, '\0', sizeof(ms));
        memset(Hs, '\0', sizeof(Hs));
        memset(ds, '\0', sizeof(ds));
        memset(Ms, '\0', sizeof(Ms));
        memset(ys, '\0', sizeof(ys));
        int cur = predeal(instr);
        DFS(instr, 0, cur);
        printEle();
    }
    return 0;
}