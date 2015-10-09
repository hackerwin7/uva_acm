#include "stdio.h"
#include "string.h"
#include "ctype.h"
#define MM 2147483647
char letters[20][10];
char in_str[500];
int w[20], cnter[20];
int C = 0, llen = 0, slen = 0, wlen = 0, Cm = 0;
int get_w(char ss[])
{
    int sum = 0;
    int ss_len = strlen(ss);
    for(int i = 0; i <= ss_len - 1; i++)
        sum = sum * 32 + (ss[i] - 'a' + 1);
    return sum;
}
int init()
{
    llen = 0;
    slen = (int)strlen(in_str);
    int k = 0;
    for(int i = 0; i<= slen - 1; i++)
    {
        if(isalpha(in_str[i]))
            letters[llen][k++] = in_str[i];
        else
        {
            if(k > 0)
            {
                letters[llen++][k] = '\0';
                w[llen - 1] = get_w(letters[llen - 1]);
            }
            k = 0;
        }
    }
    if(k > 0)
    {
        letters[llen++][k] = '\0';
        w[llen - 1] = get_w(letters[llen - 1]);
    }
    wlen = llen;
    return 0;
}
int get_max()
{
    int min = MM;
    for(int i = 0; i <= wlen - 1; i++)
        if(min > w[i])
            min = w[i];
    return min;
}
int min_C(int a, int b)
{
    return a < b ? a : b;
}
int find_C()
{
    for(int i = 0; i <= wlen - 1; i++)
        for(int j = i + 1; j <= wlen - 1; j ++)
            if(((C / w[i]) % wlen) == ((C / w[j]) % wlen))
            {
                C = min_C((C/w[i] + 1) * w[i], (C/w[j] + 1) * w[j]);
                return 0;
            }
    Cm = C;
    return 1;
}
int main()
{
    while (fgets(in_str, 500, stdin) != NULL)
    {
        if(in_str[0] == '\n') continue;
        if(in_str[strlen(in_str) - 1] == '\n')
            in_str[strlen(in_str) - 1] = '\0';
        init();
        Cm = MM;
        C = get_max();
        while (Cm == MM)
            find_C();
        printf("%s\n%d\n\n", in_str, Cm);
    }
    return 0;
}