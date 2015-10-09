#include<stdio.h>
#include<string.h>
#define MM 400000
int N=0,cases=0;
typedef struct state
{
    int maze[3][3];
    char path[100];
    int zx;
    int zy;
    int len;
    state()
    {
        memset(path, '\0', sizeof(path));
        len = 0;
    }
}state, * state_link; 
state sque[MM];
int head = 0, rear = 0;
state sur,des;
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};
int head_hash[MM],next_hash[MM];
int queue_clear()
{
    head = 0;
    rear = 0;
    return(0);
}
int push(state & elem)
{
    sque[rear++] = elem;
    return(0);
}
bool queue_empty()
{
    if(head > rear) return true;
    else return false;
}
state pop()
{
    return sque[head++];
}
int set_zxzy(state & elem)
{
    for(int i = 0; i <= 2; i++)
        for(int j = 0; j <= 2; j++)
            if(elem.maze[i][j] == 0)
            {
                elem.zx = i;
                elem.zy = j;
                return 0;
            }
    return 0;
}
int mv_state(state & elem, int i)
{
    char ch = 'U';
    int nx = 0, ny = 0;
    switch(i)
    {
    case 0:
        ch ='R';
        nx = elem.zx;
        ny = elem.zy + 1;
        break;
    case 1:
        ch = 'L';
        nx = elem.zx;
        ny = elem.zy - 1;
        break;
    case 2:
        ch = 'D';
        nx = elem.zx + 1;
        ny = elem.zy;
        break;
    case 3:
        ch = 'U';
        nx = elem.zx - 1;
        ny = elem.zy;
        break;
    }
    elem.maze[elem.zx][elem.zy] = elem.maze[nx][ny];
    elem.maze[nx][ny] = 0;
    elem.zx = nx;
    elem.zy = ny;
    elem.path[elem.len] = ch;
    elem.len++;
    elem.path[elem.len] = '\0';
    return(0);
}
int un_mv_state(state & elem, int i)
{
    switch(i)
    {
    case 0:
        mv_state(elem, 1);
        break;
    case 1:
        mv_state(elem, 0);
        break;
    case 2:
        mv_state(elem, 3);
        break;
    case 3:
        mv_state(elem, 2);
        break;
    }
    elem.len-=2;
    elem.path[elem.len] = '\0';
    return 0;
}
int get_hash(state & elem)
{
    int code = 0;
    for(int i = 0; i <= 9 - 1; i++)
        code = code * 10 + elem.maze[i/3][i%3];
    return code % MM;
}
bool is_visit(state & elem)
{
    int addr_ins = rear;
    int hash_code = get_hash(elem);
    int addr = head_hash[hash_code];
    while(addr)
    {
        if(memcmp(elem.maze, sque[addr].maze, sizeof(elem.maze)) == 0) return true;//find it!!
        addr = next_hash[addr];
    }
    next_hash[addr_ins] = head_hash[hash_code];
    head_hash[hash_code] = addr_ins;
    return false;//not find and insert it
}
int update_des(state & elem)
{
    if(elem.len > des.len) des = elem;
    return 0;
}
int BFS()
{
    while(!queue_empty())
    {
        state elem = pop();
        int ava_cnt = 0;
        for(int i = 0; i <= 4 - 1; i++)
        {
            int nx = elem.zx + dx[i];
            int ny = elem.zy + dy[i];
            if(nx >=0 && nx <= 2 && ny >= 0 && ny <= 2)
            {
                mv_state(elem, i);
                if(!is_visit(elem))
                {
                    ava_cnt ++;
                    push(elem);
                }
                un_mv_state(elem,i);
            }
        }
        if(ava_cnt == 0) update_des(elem);
    }
    return(0);
}
int print_state(state & elem)
{
    printf("%d %d %d\n",elem.maze[0][0], elem.maze[0][1], elem.maze[0][2]);
    printf("%d %d %d\n",elem.maze[1][0], elem.maze[1][1], elem.maze[1][2]);
    printf("%d %d %d\n",elem.maze[2][0], elem.maze[2][1], elem.maze[2][2]);
    printf("%s\n",elem.path);
    return 0;
}
int main()
{
    scanf("%d",&N);
    while(N--)
    {
        cases++;
        memset(des.path,'\0',sizeof(des.path));
        memset(head_hash, 0, sizeof(head_hash));
        memset(next_hash, 0, sizeof(next_hash));
        des.len = 0;
        scanf("%d%d%d",&sur.maze[0][0],&sur.maze[0][1],&sur.maze[0][2]);
        scanf("%d%d%d",&sur.maze[1][0],&sur.maze[1][1],&sur.maze[1][2]);
        scanf("%d%d%d",&sur.maze[2][0],&sur.maze[2][1],&sur.maze[2][2]);
        set_zxzy(sur);
        queue_clear();
        push(sur);
        BFS();
        printf("Puzzle #%d\n",cases);
        print_state(des);
        printf("\n");
    }
    return(0);
}
