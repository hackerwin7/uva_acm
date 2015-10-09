#include<stdio.h>
#include<algorithm>
using namespace std;
int s[1000] = {0}, a = 0, b = 0, c = 0, d = 0, n = 0;
int main()
{
    while (scanf("%d", &n) != EOF && n > 0)
    {
        int i, j, k, m, sum = 0;
        for(i = 0; i <= n - 1; i++) scanf("%d", &s[i]);
        sort(s, s + n);// once equals, it must be max
        for(i = n - 1; i >= 0; i--)
        {
            d = s[i];
            for(j = n - 1; j >= 0; j--)
            {
                c = s[j];
                if(c == d) continue;
                for(k = n - 1; k >= 0; k--)
                {
                    b = s[k];
                    if(b == c || b == d) continue;
                    for(m = n - 1; m >= 0; m--)
                    {
                        a = s[m];
                        if(a == b || a == c || a == d) continue;
                        sum = a + b + c;
                        if(sum == d) break;
                    }
                    if(sum == d) break;
                }
                if(sum == d) break;
            }
            if(sum == d) break;
        }
        if(n >= 4 && sum == d) printf("%d\n", d);
        else printf("no solution\n");
    }
    return 0;
}