#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define DM 199
#define NN 1000
int main()
{
    int a,b,c,d;
    int t = NN;
    while(t--)
    {
        a = rand()%DM + 1;
        b = rand()%DM + 1;
        c = rand()%DM + 1;
        d = rand()%DM + 1;
        printf("%d %d %d %d\n",a,b,c,d);
    }
    return 0;
}