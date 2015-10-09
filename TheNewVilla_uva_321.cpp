#include<stdio.h>
#include<string.h>
#define MS 1000003
int r,d,s;
bool door_con[100][100]={false};//begin with 1, undirected graph
bool switch_con[100][100]={false};//begin with 1, directed graph
int cases = 0;
typedef struct st
{
    int rooms[15];//0 is light off and 1 is light on,  begin with 1
    int pos;//the people in the room with number
    int ft[100];//footprint,begin with 0;+2 -> switch on 2 room , -2 -> switch off 2 room , 200 -> move to 2 room
    int ft_len;
    st()
    {
        memset(rooms, 0, sizeof(rooms));
        pos = 0;
        memset(ft, 0, sizeof(ft));
        ft_len = 0;
    }
}st, * st_link;
int head[MS], next[MS];
st sq[MS];
int front = 0, rear = 0;
bool is_reached(int cur)
{
    if(sq[cur].pos != r)
        return false;
    for(int i = 1; i <= r - 1; i++)
        if(sq[cur].rooms[i] == 1)//1 ~ r-1 room must be off light
            return false;
    if(sq[cur].rooms[r] == 0)//r room must be on light
        return false;
    return true;
}
int clone_st(int src, int des)
{
    memcpy(sq[src].rooms, sq[des].rooms, sizeof(sq[src].rooms));
    memcpy(sq[src].ft, sq[des].ft, sizeof(sq[src].ft));
    sq[src].pos = sq[des].pos;
    sq[src].ft_len = sq[des].ft_len;
    return 0;
}
int BKDR_hash(st cur)
{
    int seed = 131;
    int hash = 0;
    for (int i = 1; i <= r; i++)
    {
        hash += hash * seed + cur.rooms[i];
    }

    return hash % MS;
}
int sq_cmp(int s1, int s2)
{
    if(sq[s1].pos != sq[s2].pos)
        return 1;
    for(int i = 1; i <= r; i++)
        if(sq[s1].rooms[i] != sq[s2].rooms[i])
            return 1;
    return 0;
}
int try_to_insert(int s)
{
    int h = BKDR_hash(sq[s]);
    int u = head[h];
    while (u)
    {
        if(sq_cmp(u, s) == 0) return 0;
        u = next[u];
    }
    next[s] = head[h];
    head[h] = s;
    return 1;
}
int BFS()
{
    //init the first status
    sq[rear].rooms[1] = 1;
    sq[rear].pos = 1;
    sq[rear].ft_len = 0;
    rear ++;
    while (front < rear)
    {
        //sq[front] is pop father, then generate kinds of children
        if(is_reached(front)) return 1;
        //switch on/off light
        for(int i = 1; i <= r; i++)
        {
            if(switch_con[sq[front].pos][i])
            {
                clone_st(rear, front);
                sq[rear].rooms[i] = sq[rear].rooms[i] ^ 1;// 0 ^ 1 = 1 , 1 ^ 1 = 1. just like switch
                if(sq[rear].rooms[i] == 0 && sq[front].pos == i)//the people at the room which must be on light
                    continue;
                if(try_to_insert(rear))
                {
                    if(sq[rear].rooms[i] == 0) sq[rear].ft[sq[rear].ft_len++] = 0 - i;//record footprint , switch off
                    else sq[rear].ft[sq[rear].ft_len++] = i;//switch on
                    rear++;//push the children to the queue
                }
            }
        }
        //move to room
        for(int i = 1; i <= r; i++)
        {
            if(door_con[sq[front].pos][i] || door_con[i][sq[front].pos])//connected room
            {
                if(sq[front].rooms[i] == 1)//move the room which must be on light
                {
                    clone_st(rear, front);
                    sq[rear].pos = i;//move to the i room
                    if(try_to_insert(rear))
                    {
                        sq[rear].ft[sq[rear].ft_len++] = i * 100;//foot print
                        rear++;
                    }
                }
            }
        }
        front++;//pop the father
    }
    return 0;
}
int print_st(int cur)
{
    printf("The problem can be solved in %d steps:\n", sq[cur].ft_len);
    for(int i = 0; i <= sq[cur].ft_len - 1; i++)
    {
        if(sq[cur].ft[i] < 0)
            printf("- Switch off light in room %d.\n", 0 - sq[cur].ft[i]);
        if(sq[cur].ft[i] > 0 && sq[cur].ft[i] < 100)
            printf("- Switch on light in room %d.\n", sq[cur].ft[i]);
        if(sq[cur].ft[i] >= 100)
            printf("- Move to room %d.\n", sq[cur].ft[i] / 100);
    }
    return 0;
}
int main()
{
    while(scanf("%d%d%d",&r,&d,&s)!=EOF && (r + d + s) > 0)
    {
        memset(door_con, false, sizeof(door_con));
        memset(switch_con, false, sizeof(switch_con));
        memset(head, 0, sizeof(head));
        memset(next, 0, sizeof(next));
        front = rear = 0;
        cases++;
        for(int i = 1; i <= d; i++)
        {
            int indoor = 0, outdoor = 0;
            scanf("%d%d",&indoor, &outdoor);
            door_con[indoor][outdoor] = true;
            door_con[outdoor][indoor] = true;
        }
        for(int i = 1; i <= s; i++)
        {
            int doorn = 0, doorl = 0;
            scanf("%d%d", &doorn, &doorl);
            switch_con[doorn][doorl] = true;
        }
        printf("Villa #%d\n", cases);
        if(BFS() == 1)
            print_st(front);
        else
            printf("The problem cannot be solved.\n");
        printf("\n");
    }
    return(0);
}
