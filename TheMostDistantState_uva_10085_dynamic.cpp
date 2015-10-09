#include<stdio.h>
#include<string.h>
#include<time.h>
bool is_vis[876543211]={false};
typedef struct state
{
    int maze[3][3];
    char path[100];
    int zx;
    int zy;
    struct state * next;
    state()
    {
        memset(path,'\0',sizeof(path));
        next = NULL;
    }
}state, * state_link;
state_link head = NULL, rear = NULL;
int N=0,cases=0;
int dx[4] = {0,0,1,-1};
int dy[4] = {1,-1,0,0};
bool queue_empty()
{
    if(head == NULL && rear == NULL) return true;
    return false;
}
state_link pop()
{
    if(queue_empty()) return NULL;
    if(head == rear)//only 1 left
    {
        state_link pelem = head;
        head = NULL;
        rear = NULL;
        return pelem;
    }
    else
    {
        state_link pelem = head;
        head = head->next;
        return pelem;
    }
}
state_link cpy_from(state_link elem)
{
    if(elem == NULL) return NULL;
    state_link new_elem = new state();
    for(int i = 0; i <= 3 - 1; i++)
        for(int j = 0; j <= 3 - 1; j++)
            new_elem->maze[i][j] = elem->maze[i][j];
    strcpy(new_elem->path, elem->path);
    new_elem->zx = elem->zx;
    new_elem->zy = elem->zy;
    new_elem->next = NULL;
    return new_elem;
}
int push(state_link elem)
{
    if(elem == NULL) return 0;
    state_link new_pot = cpy_from(elem);
    if(head == NULL && rear == NULL)
    {
        head=new_pot;
        rear=new_pot;
    }
    else if(head != NULL && rear != NULL)
    {
        rear->next = new_pot;
        rear = new_pot;
    }
    return 0;
}
int set_zxzy(state_link elem)
{
    for(int i=0;i<=3-1;i++)
        for(int j=0;j<=3-1;j++)
            if(elem->maze[i][j] == 0)
            {
                elem->zx = i;
                elem->zy = j;
                return 0;
            }
    return(0);
}
bool is_visit(state_link elem)
{
    if(elem == NULL) return true;
    int hash_code = 0;
    for(int i = 0; i <= 9 - 1; i++)
        hash_code = hash_code * 10 + elem->maze[i/3][i%3];
    if(is_vis[hash_code]) return true;
    else
    {
        is_vis[hash_code] = true;
        return false;
    }
}
int cmp_des(state & cur, state & des)
{
    int cur_len = strlen(cur.path);
    int des_len = strlen(des.path);
    if(cur_len <= des_len) return 0;
    else
    {
        for(int i = 0; i <= 3 - 1; i++)
            for(int j = 0; j <= 3 - 1; j++)
                des.maze[i][j] = cur.maze[i][j];
        strcpy(des.path, cur.path);
    }
    return(0);
}
state_link mv_state(state_link elem,int nx,int ny,int i)
{
    if(elem == NULL) return NULL;
    char ch = 'U';
    switch(i)
    {
    case 0:
        ch = 'R';
        break;
    case 1:
        ch = 'L';
        break;
    case 2:
        ch = 'D';
        break;
    case 3:
        ch = 'U';
        break;
    }
    state_link new_elem = cpy_from(elem);
    int tmp = new_elem->maze[elem->zx][elem->zy];
    new_elem->maze[elem->zx][elem->zy] = new_elem->maze[nx][ny];
    new_elem->maze[nx][ny] = tmp;
    new_elem->zx = nx;
    new_elem->zy = ny;
    int old_len = strlen(new_elem->path);
    new_elem->path[old_len] = ch;
    new_elem->path[old_len + 1] = '\0';
    return new_elem;
}
int BFS(state &sur, state &des)
{
    while(!queue_empty())
    {
        state_link elem = pop();
        int ava_cnt = 0;
        for(int i=0;i<=4-1;i++)
        {
            int nx = elem->zx + dx[i];
            int ny = elem->zy + dy[i];
            if(nx >=0 && nx <= 2 && ny >= 0 && ny <= 2)
            {
                state_link nelem = mv_state(elem,nx,ny,i);
                if(!is_visit(nelem))
                {
                    ava_cnt++;
                    push(nelem);
                }
            }
        }
        if(ava_cnt == 0) cmp_des(*elem, des);
        delete elem;
        elem = NULL;
    }
    return 0;
}
int print_state(state st)
{
    printf("%d %d %d\n",st.maze[0][0],st.maze[0][1],st.maze[0][2]);
    printf("%d %d %d\n",st.maze[1][0],st.maze[1][1],st.maze[1][2]);
    printf("%d %d %d\n",st.maze[2][0],st.maze[2][1],st.maze[2][2]);
    printf("%s\n",st.path);
    return 0;
}
int clear_queue()
{
    if(head == NULL && rear == NULL) return 0;
    state_link pot = head;
    while(pot != NULL)
    {
        state_link tmp = pot;
        pot = pot->next;
        delete tmp;
    }
    head = rear = NULL;
    return 0;
}
int main()
{
    scanf("%d",&N);
    while(N--)
    {
        cases++;
        memset(is_vis,false,sizeof(is_vis));
        clear_queue();
        state sur;
        scanf("%d%d%d",&sur.maze[0][0],&sur.maze[0][1],&sur.maze[0][2]);
        scanf("%d%d%d",&sur.maze[1][0],&sur.maze[1][1],&sur.maze[1][2]);
        scanf("%d%d%d",&sur.maze[2][0],&sur.maze[2][1],&sur.maze[2][2]);
        set_zxzy(&sur);
        state des;
        push(&sur);
        BFS(sur,des);
        printf("Puzzle #%d\n",cases);
        print_state(des);
        printf("\n");
    }
    return(0);
}
