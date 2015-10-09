//
// Created by hp on 9/22/15.
//
#include<stdio.h>
char in[20] = {'\0'};
int main()
{
    while(scanf("%s", in) != EOF)
        printf("%s,", in);
    return 0;
}
