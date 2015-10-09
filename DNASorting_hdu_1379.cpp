#include<stdio.h>
#include<algorithm>
using namespace std;
typedef struct dna
{
    char str[55];
    int ranks;
    int sorts;
}dna,* dna_link;
dna dd[100];
int n=0,m=0,t=0;
bool comp(dna a, dna b)
{
    if(a.sorts < b.sorts) return true;
    else if(a.sorts > b.sorts) return false;
    else return a.ranks < b.ranks;
}
int main()
{
    while(scanf("%d",&t)!=EOF)
    {
        int cases=0;
        while(t--)
        {
            cases++;
            scanf("%d%d",&n,&m);
            for(int i=0;i<m;i++)
            {
                scanf("%s",dd[i].str);
                dd[i].ranks=i;
                dd[i].sorts=0;//initialize
                for(int k1=0;k1<n;k1++)
                {
                    for(int k2=k1+1;k2<n;k2++)
                    {
                        if(dd[i].str[k1]>dd[i].str[k2]) dd[i].sorts++;
                    }
                }
            }
            sort(dd,dd+m,comp);
            for(int i=0;i<m;i++) printf("%s\n",dd[i].str);
            if(cases>1) printf("\n");
        }
    }
    return(0);
}
