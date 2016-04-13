//
// Created by fff on 4/8/16.
//
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
int f[200 + 5] = {0}, sz[200 + 5] = {0}, deg[200 + 5] = {0};
int N = 0, R = 0, u_cnt = 0, z_cnt = 0;
int init(int n) {
    for(int i = 0; i <= n - 1; i++) {
        f[i] = i;
        sz[i] = 1;
    }
    return 0;
}
int recur_finds(int x) {
    if(x != f[x]) f[x] = recur_finds(f[x]);//path compression
    return f[x];
}
int finds(int x) {
    while (x != f[x]) x = f[x];
    return x;
}
int unions(int x, int y) {
    int xi = finds(x);
    int yi = finds(y);
    f[x] = xi;// path compression
    f[y] = yi;
    if(xi != yi) {
        if(sz[xi] > sz[yi]) {
            f[yi] = xi;// xi as yi's father
            sz[xi] += sz[yi];
        } else {
            f[xi] = yi;
            sz[yi] += sz[xi];
        }
        u_cnt --;
    }
    return 0;
}
int main() {
    while (scanf("%d%d", &N, &R) != EOF) {
        init(N);
        memset(deg, 0, sizeof(deg));
        u_cnt = N;
        z_cnt = 0;
        for(int i = 0; i <= R - 1; i++) {
            int s = 0, d = 0;
            scanf("%d%d", &s, &d);
            unions(s, d);
            deg[s]++;
            deg[d]++;
        }
        for(int i = 0; i <= N - 1; i++)
            if(deg[i] == 0)
                z_cnt++;
        if(u_cnt != (z_cnt + 1)) // tricky
            printf("Not Possible\n");
        else {
            int i = 0;
            for(i = 0; i <= N - 1; i++)
                if(deg[i] % 2 != 0)
                    break;
            if(i <= N - 1) printf("Not Possible\n");
            else printf("Possible\n");
        }
    }
    return 0;
}