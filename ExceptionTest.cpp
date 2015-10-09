#include<stdio.h>
#include<string>
#include<iostream>
using namespace std;
int main()
{
    int a = 0;
    
    try
    {
        int* p = new int(0);
        *p = 1;
    }
    catch(...)
    {
        printf("catch exception...\n");
    }
    printf("length : %d\n",a);
    return(0);
}
