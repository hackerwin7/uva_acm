#include "stdio.h"
#include "string.h"
#define DM 1000003
int n = 0;
typedef struct stat
{
    int puz[2][12];// puz[0] is left , puz[1] is right
    int ft[16];
    int ft_len;
    struct stat * next;
    stat()
    {
        ft_len = 0;
        next = NULL;
    }
}stat, * stat_link;
stat_link front = NULL, rear = NULL, res = NULL;
int best_left[12] = {0, 3, 4, 3, 0, 5, 6, 5, 0, 1, 2, 1};
int best_right[12] = {0, 7, 8, 7, 0, 9, 10, 9, 0, 1, 2, 1};
int in_left[12], in_right[12];
stat_link hash_table[DM] = {NULL};
bool is_empty()
{
    if(front == NULL && rear == NULL)
        return true;
    else
        return false;
}
void push(stat_link pot)
{
    if(is_empty())
    {
        front = rear = pot;
    }
    else
    {
        pot->next= NULL;
        rear->next = pot;
        rear = rear->next;
    }
}
stat_link pop()
{
    if(is_empty() || front == NULL) return NULL;
    stat_link tmp = front;
    front = front->next;
    if(front == NULL) rear = NULL;//the queue only have one elementary
    return tmp;
}
bool is_reached(stat_link pot)
{
    if(memcmp(best_left, pot->puz[0], sizeof(best_left)) == 0 && memcmp(best_right, pot->puz[1], sizeof(best_right)) == 0)
        return true;
    else
        return false;
}
stat_link clone_st(stat_link pot)
{
    if(pot == NULL)
        return NULL;
    stat_link clone = new stat();
    memmove(clone, pot, sizeof(*pot));
    clone->next = NULL;
    return clone;
}
int BKDR_hash(stat_link sl)
{
    if(sl == NULL) return -1;
    int seed = 131;
    int res = 0;
    for(int i = 0; i <= 11; i++)//left
        res = (res * seed + sl->puz[0][i]) % DM;
    for(int i = 0; i <= 8; i++)//right
        res = (res * seed + sl->puz[1][i]) % DM;
    return res % DM;
}
int try_to_insert(stat_link sl)
{
    if(sl == NULL) return 0;
    stat_link nsl = clone_st(sl);
    int h = BKDR_hash(nsl);
    if(h < 0) return 0;
    stat_link u = hash_table[h];
    while (u)
    {
        if(memcmp(u->puz[0], nsl->puz[0], sizeof(nsl->puz[0])) == 0 && memcmp(u->puz[1], nsl->puz[1], sizeof(nsl->puz[1])) == 0)
            return 0;
        u = u->next;
    }
    stat_link tmp = hash_table[h];
    hash_table[h] = nsl;
    hash_table[h]->next = tmp;
    return 1;
}
int print_st(stat_link pot)
{
    if(pot == NULL) return 0;
    if(pot->ft_len == 0)
        printf("PUZZLE ALREADY SOLVED");
    else
        for(int i = 0; i <= pot->ft_len - 1; i++)
            printf("%d", pot->ft[i]);
    printf("\n");
    return 0;
}
int BFS()
{
    //init the first father
    stat_link elem = NULL;
    elem = new stat();
    memmove(elem->puz[0], in_left, sizeof(elem->puz[0]));//memcpy and strcpy for memory overlap problem
    memmove(elem->puz[1], in_right, sizeof(elem->puz[1]));
    push(elem);
    while (!is_empty())
    {
        stat_link father = pop(), child = NULL;
        if(father->ft[0] == 1)
            print_st(father);
        if(is_reached(father))
        {
            res = father;
            return 1;
        }
        if(father->ft_len >= 16) continue;
        //generate children from the father
        for(int m = 1; m <= 4 ; m++)//m is mode, 1 ~ 4 indicate that left+clockwise, right+clockwise ......
        {
            child = clone_st(father);
            int stp = 0;//clockwise 2 or counter clockwise -2
            if(m == 1 || m == 4) stp = 2;
            else stp = -2;
            int whe = (m % 2) ^ 1, un_whe = m % 2;//left 0 or right 1
            int tmp[12];
            for(int i = 0; i <= 12 - 1; i++)
            {
                int next_i = i + stp;
                if(next_i < 0) next_i = 12 + next_i;
                if(next_i > 11) next_i = next_i - 12;
                tmp[next_i] = child->puz[whe][i];
            }
            memmove(child->puz[whe], tmp, sizeof(child->puz[whe]));
            child->puz[un_whe][11] = child->puz[whe][11];
            child->puz[un_whe][10] = child->puz[whe][10];
            child->puz[un_whe][9] = child->puz[whe][9];
            child->ft[child->ft_len++] = m;
            if(child->ft_len <= 16 && try_to_insert(child))
                push(child);
            else
                if(child != NULL) delete child;
            child = NULL;
        }
        if(father != NULL) delete father;
        father = NULL;
    }
    return 0;
}
int clear_queue()
{
    stat_link pot = front;
    stat_link tmp = NULL;
    while(!is_empty())
    {
        tmp = pot;
        pot = pot->next;
        front = pot;
        if(tmp != NULL) delete tmp;
        tmp = NULL;
    }
    if(res != NULL) delete res;
    front = rear = res = NULL;
    return 0;
}
int clear_hash()
{
    for(int i = 0; i <= DM - 1; i++)
    {
        stat_link pot = hash_table[i];
        while (pot != NULL)
        {
            stat_link tmp = pot;//hash_table must save new struct that is different from queue's struct
            pot = pot->next;//I know why double free, see try_to_insert() carefully, the insert elem is queue elem , it is same struct , so when queue is clear then the hash_table's elem is deleted too
            if(tmp != NULL) delete tmp;//maybe the memory is overlap
            tmp = NULL;
        }
        hash_table[i] = NULL;
    }
    return 0;
}
int main()
{
    while (scanf("%d", &n) !=  EOF && n > 0)
    {
        while (n--)
        {
            front = rear = res = NULL;
            for(int i = 0; i <= 12 - 1; i++)
                scanf("%d", &in_left[i]);
            for(int i = 0; i <= 12 - 1; i++)
                scanf("%d", &in_right[i]);
            if(BFS())
                print_st(res);
            else
                printf("NO SOLUTION WAS FOUND IN 16 STEPS\n");
            clear_queue();
            clear_hash();//double free error
        }
    }
    return 0;
}