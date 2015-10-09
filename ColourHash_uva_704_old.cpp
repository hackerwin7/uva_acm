//
// Created by hp on 15-3-25.
//
#include "stdio.h"
#include<string.h>
#define MAXSTEP 16
#define MM 1000003//WA : the generated children is so huge that this MM index cannot include these children, we can think about link list to express the queue
int n = 0;
typedef struct stat
{
    int color[24];
    int ft[16];
    int ft_len;
    stat()
    {
        memset(color, 0, sizeof(color));
        ft_len = 0;
    }
}stat, * stat_link;
stat st[MM];//queue
int head[MM], next[MM];
int final_color[24] = {0, 3, 4, 3, 0, 5, 6, 5, 0, 1, 2, 1, 0, 7, 8, 7, 0, 9, 10, 9, 0, 1, 2, 1};
int front = 0, rear = 0;
int wheels[4] = {0, 12, 0, 12};
int clockwise[4] = {2, 2, -2, -2};
bool is_reached(int cur)
{
    if(st[cur].ft_len > MAXSTEP) return false;
    if(memcmp(st[cur].color, final_color, sizeof(final_color)) != 0) return false;
    return true;
}
int clone_st(int src, int des)
{
    memcpy(st[src].color, st[des].color, sizeof(st[src].color));
    memcpy(st[src].ft, st[des].ft, sizeof(st[src].ft));
    st[src].ft_len = st[des].ft_len;
    return 0;
}
int mv_2(int bgn, int src, int dire)//mv dire steps for dire direction
{
    //only for 0 ~ 11 not for 12 ~ 23
    if(bgn == 0)
    {
        int res = src + dire;
        if(res > 11)//dire > 0
            return (res - 11 - 1);//begin with 0
        if(res < 0)
            return (11 + res + 1);
    }
    else
    {
        int res = src + dire;
        if(res > 23)//dire > 0
            return (res - 23 - 1 + 12);//begin with 0
        if(res < 12)
            return (23 + res - 12 + 1);
    }
}
int BKDR_hash(stat s)
{
    int hash = 0;
    int seed = 131;
    for(int i = 0; i <= 24 - 1; i++)
        hash = hash * seed + s.color[i];
    return hash % MM;
}
int try_to_insert(int s)
{
    int h = BKDR_hash(st[s]);
    int u = head[h];
    while (u)
    {
        if(memcmp(st[u].color, st[s].color, sizeof(st[s].color)) == 0) return 0;//map have exist it, st[s] is repeated
        u = next[u];
    }
    next[s] = head[h];
    head[h] = s;
    return 1;
}
int parse_op(int wheel_start, int direction)
{
    if(wheel_start == 0)//left wheel
    {
        if(direction > 0)//clockwise
            return 1;
        else//counter-clockwise
            return 3;
    }
    else
    {
        if(direction > 0)//counter-clockwise
            return 4;
        else//clockwise
            return 2;
    }
}
int print_st(int cur)
{
    if(st[cur].ft_len == 0)
        printf("PUZZLE ALREADY SOLVED");
    else
    {
        for (int i = 0; i <= st[cur].ft_len - 1; i++)
            printf("%d", st[cur].ft[i]);
    }
    printf("\n");
    return 0;
}
int debug_arr[12] = {1,4,3,4,3,3,2,3,3,4,3,3};
int adj_3(int cur, int wheel)
{
    if(wheel == 0)//left -> right
    {
        st[cur].color[23] = st[cur].color[11];
        st[cur].color[22] = st[cur].color[10];
        st[cur].color[21] = st[cur].color[9];
    }
    else
    {
        st[cur].color[11] = st[cur].color[23];
        st[cur].color[10] = st[cur].color[22];
        st[cur].color[9] = st[cur].color[21];
    }
    return 0;
}
int BFS()
{
    while (front < rear)
    {
        //pop the father
        if (is_reached(front)) return 1;
        int flag = 0;
//        printf("fr: %d %d\n", front, rear);
        print_st(front);
        if(st[front].ft_len == 12 && memcmp(debug_arr, st[front].ft, sizeof(debug_arr)) == 0)
        {
            flag = 1;
            print_st(front);
            for(int i = 0; i <= 24 -1; i++) printf("%d", st[front].color[i]);
            printf("\n");
        }
        if(st[front].ft_len >= MAXSTEP)
        {
            front++;//pop it
            continue;//prune
        }
        //generate children
        for(int di = 0; di <= 4 - 1; di++)
        {
            clone_st(rear, front);
            int bgn = wheels[di], dir = clockwise[di];
            int mv_cnt = 0;
            int src = bgn, des = 0, src1 = bgn + 1, des1 = 0;
            int tmp = st[rear].color[src], tmp1 = st[rear].color[src1];
            int tmps = 0, tmps1 = 0;//temp save var
            if(flag == 1)
            {
                for(int i = 0; i <= 24 - 1; i++) printf("%d,", st[front].color[i]);
                printf("\n---> %d\n", parse_op(bgn, dir));
            }
            do
            {
                des = mv_2(bgn, src, dir);
                if(flag == 1)
                {
                    printf("** %d %d\n", src, des);
                }
                des1 = mv_2(bgn, src1, dir);
                tmps = st[rear].color[des];
                st[rear].color[des] = tmp;
                tmp = tmps;
                tmps1 = st[rear].color[des1];
                st[rear].color[des1] = tmp1;
                tmp1 = tmps1;
                src = des;
                src1 = des1;
                mv_cnt++;
            }while (mv_cnt < 6);
            //adjust last 3 digit
            adj_3(rear, bgn);
            if(flag == 1)
            {
                printf("rotation:");
                for(int i = 0; i <= 24 - 1; i++) printf("%d,", st[rear].color[i]);
                printf("\n");
            }
            if(try_to_insert(rear))
            {
                if(flag == 1)
                    printf("pass hash\n");
                st[rear].ft[st[rear].ft_len++] = parse_op(bgn, dir);
                if(st[rear].ft_len <= MAXSTEP)
                {
                    if(flag == 1)
                    {
                        printf("pass len : ");
                        print_st(rear);
                    }
                    rear++;//push the queue
                    printf("add the rear : %d\n" , rear - 1);
                }
            }
        }
        front++;
    }
    return 0;
}
int main()
{
    while (scanf("%d", &n)!=EOF && n > 0)
    {
        while (n--)
        {
            printf("##%d:\n", n);
            memset(head, 0, sizeof(head));
            memset(next, 0, sizeof(next));
            front = rear = 0;
            //init source status and push the queue
            for(int i = 0; i <= 24 - 1; i++)
                scanf("%d", &st[rear].color[i]);
            st[rear].ft_len = 0;
            try_to_insert(rear);//add hash
            rear++;
            if(BFS())
                print_st(front);
            else
                printf("NO SOLUTION WAS FOUND IN 16 STEPS\n");
        }
    }
    return 0;
}