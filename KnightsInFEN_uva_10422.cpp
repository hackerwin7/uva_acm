#include<stdio.h>
#include<string.h>
#define DL 10
#define DI 5
#define MM 1000
#define DD 8
#define HS 1000001//hash size
#define HH 0x7FFFFFFF
int N = 0;
typedef struct node
{
    char mat[DI+5][DI+5];
    int len;
    node * next;
    int x;//the position of ' '
    int y;
    node()
    {
        memset(mat, '\0', sizeof(mat));
        len = 0;
        next = NULL;
    }
}node, * node_link;
node_link min_node = NULL;
node_link target_node = NULL;
node_link head = NULL, rear = NULL;
int dx[DD] = {-2, -2, -1,  1,  2, 2, -1, 1};//8 directions walk
int dy[DD] = {-1,  1, -2, -2, -1, 1,  2, 2};
node_link hash_table[HS + 5];
void delete_pot(node_link & elem)
{
    if(elem != NULL)
    {
        delete elem;
        elem = NULL;
    }
}
void nodelinkcpy(node_link & e1, node_link e2)
{
    if(e2 == NULL) return;
    if(e1 == NULL) e1 = new node();
    for(int i = 0; i <= DI - 1; i++)
        for(int j = 0; j <= DI - 1; j++)
            e1->mat[i][j] = e2->mat[i][j];
    e1->x = e2->x;
    e1->y = e2->y;
    e1->len = e2->len;
    e1->next = e2->next;
}
bool is_mat_equal(node_link e1, node_link e2)
{
    if(e1 == NULL || e2 == NULL) return false;
    for(int i = 0; i <= DI - 1; i++)
        for(int j = 0; j <= DI - 1; j++)
            if(e1->mat[i][j] != e2->mat[i][j])
                return false;
    return true;
}
int bkdr_hash(node_link elem)
{
    if(elem == NULL) return -1;
    int seed_value = 131;
    int hash_value = 0;
    for(int i = 0; i <= DI - 1; i++)
        for(int j = 0; j <= DI - 1; j++)
            hash_value = hash_value * seed_value + elem->mat[i][j];
    return (hash_value & HH) % HS;
}
bool is_vis(node_link elem)
{
    int ind = bkdr_hash(elem);
    if(hash_table[ind] == NULL)
    {
        //add the new hash elem
        node_link new_ele = NULL;
        nodelinkcpy(new_ele, elem);
        new_ele->next = NULL;
        hash_table[ind] = new_ele;
        return false;
    }
    else
    {
        node_link hhead = hash_table[ind];
        node_link pot = hhead;
        while(pot != NULL)
        {
            if(is_mat_equal(pot, elem)) return true;//find it in hash table
            pot = pot->next;
        }
        //not find it , then the elem is conflict hash elem
        node_link new_ele = NULL;
        nodelinkcpy(new_ele, elem);
        new_ele->next = hash_table[ind];
        hash_table[ind] = new_ele;
        return false;
    }
}
void clear_hash()
{
    for(int i = 0; i <= HS + 5 - 1; i++)
    {
        if(hash_table[i] != NULL)
        {
            node_link pot = hash_table[i];
            while(pot != NULL)
            {
                node_link temp = pot;
                pot = pot->next;
                delete_pot(temp);
            }
            hash_table[i] = NULL;
        }
    }
}
void findxy(node_link elem)
{
    if(elem!=NULL)
        for(int i = 0; i <= DI - 1; i++)
            for(int j = 0; j <= DI - 1; j++)
                if(elem->mat[i][j] == ' ')
                {
                    elem->x = i;
                    elem->y = j;
                    return;
                }
}
void print_mat(node_link elem)
{
    if(elem != NULL)
        for(int i = 0; i <= DI - 1; i++)
            printf("%s\n", elem->mat[i]);
}
bool is_reached(node_link elem)
{
    if(elem == NULL || target_node == NULL) return false;
    if(elem->len > DL) return false;
    for(int i = 0; i <= DI - 1; i++)
        for(int j = 0; j <= DI - 1; j++)
            if(target_node->mat[i][j] != elem->mat[i][j]) return false;
    return true;
}
bool queue_empty()
{
    if(head == NULL && rear == NULL) return true;
    else return false;
}
void push(node_link elem)
{
    if(elem != NULL)
    {
        node_link add_ele = NULL;
        nodelinkcpy(add_ele, elem);
        if(queue_empty())
        {
            head = add_ele;
            rear = add_ele;
        }
        else
        {
            rear->next = add_ele;
            rear = rear->next;
        }
    }
}
node_link pop()
{
    if(queue_empty()) return NULL;
    node_link pop_ele = head;
    head = head->next;
    if(head == NULL) rear = NULL;
    return pop_ele;
}
node_link move_space(node_link old_ele, int tx, int ty)
{
    if(old_ele == NULL) return NULL;
    if(tx < 0 || ty < 0 || tx > DI - 1 || ty > DI - 1) return NULL;
    node_link new_ele = NULL;
    nodelinkcpy(new_ele, old_ele);
    char temp = new_ele->mat[new_ele->x][new_ele->y];
    new_ele->mat[new_ele->x][new_ele->y] = new_ele->mat[tx][ty];
    new_ele->mat[tx][ty] = temp;
    new_ele->x = tx;
    new_ele->y = ty;
    new_ele->len = old_ele->len + 1;
    new_ele->next = NULL;
    return new_ele;
}
void queue_clear()
{
    if(!queue_empty())
    {
        node_link pot = head;
        while(pot!=NULL)
        {
            node_link tmp = pot;
            pot = pot->next;
            delete_pot(tmp);
        }
    }
    head = rear = NULL;
}
int main()
{
    target_node = new node();
    strcpy(target_node->mat[0],"11111");
    strcpy(target_node->mat[1],"01111");
    strcpy(target_node->mat[2],"00 11");
    strcpy(target_node->mat[3],"00001");
    strcpy(target_node->mat[4],"00000");
    scanf("%d",&N);
    while(N--)
    {
        node_link in_node = new node();
        for(int i = 0; i <= DI - 1; i++)
        {
            char instr[100];
            fgets(instr, 100, stdin);//note the input include the ' ' can not use scanf("%s")
            while(instr[0] == '\n') fgets(instr, 100, stdin);
            if(instr[strlen(instr) - 1] == '\n') instr[strlen(instr) - 1] = '\0';
            strcpy(in_node->mat[i], instr);
        }
        findxy(in_node);
        if(is_reached(in_node))
        {
            printf("Solvable in %d move(s).\n", 0);
            delete_pot(in_node);
            continue;
        }
        if(!is_vis(in_node)) push(in_node);
        delete_pot(in_node);
        while(!queue_empty())
        {
            node_link center = pop();
            if(is_reached(center)) 
            {
                nodelinkcpy(min_node, center);
                delete_pot(center);
                break;
            }
            //move the space to 8 directions to move space
            for(int i = 0; i <= DD - 1; i++)
            {
                node_link moved = move_space(center, center->x + dx[i], center->y + dy[i]);
                if(moved != NULL && moved->len <= DL && !is_vis(moved)) push(moved);
                delete_pot(moved);
            }
            delete_pot(center);
        }
        if(min_node == NULL) printf("Unsolvable in less than 11 move(s).\n");
        else printf("Solvable in %d move(s).\n", min_node->len);
        delete_pot(min_node);
        queue_clear();
        clear_hash();
    }
    return 0;
}
