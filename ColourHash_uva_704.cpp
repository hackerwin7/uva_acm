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
stat_link front = NULL, rear = NULL, res = NULL;//start -> bfs
stat_link end_front = NULL, end_rear = NULL, res_end = NULL, find_stat = NULL;
int best_left[12] = {0, 3, 4, 3, 0, 5, 6, 5, 0, 1, 2, 1};
int best_right[12] = {0, 7, 8, 7, 0, 9, 10, 9, 0, 1, 2, 1};
int in_left[12], in_right[12];
stat_link hash_table[DM] = {NULL};
stat_link hash_table_end[DM] = {NULL};
bool is_empty()
{
    if(front == NULL && rear == NULL)
        return true;
    else
        return false;
}
bool is_empty_end()
{
    if(end_front == NULL && end_rear == NULL)
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
void push_end(stat_link pot)
{
    if(is_empty_end())
    {
        end_front = end_rear = pot;
    }
    else
    {
        pot->next = NULL;
        end_rear->next = pot;
        end_rear = end_rear->next;
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
stat_link pop_end()
{
    if(is_empty_end() || end_front == NULL) return NULL;
    stat_link tmp = end_front;
    end_front = end_front->next;
    if(end_front == NULL) end_rear = NULL;//the queue only have one elementary
    return tmp;
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
bool is_in_hash(stat_link pot, stat_link table[])
{
    int h = BKDR_hash(pot);
    stat_link u = table[h];
    while (u)
    {
        if(memcmp(u->puz[0], pot->puz[0], sizeof(pot->puz[0])) == 0 && memcmp(u->puz[1], pot->puz[1], sizeof(pot->puz[1])) == 0)
        {
            find_stat = u;
            return true;
        }
        u = u->next;
    }
    return false;
}
bool is_reached(stat_link pot)
{
    if(is_in_hash(pot, hash_table_end))
        return true;
    else
        return false;
}
bool is_reached_end(stat_link pot)
{
    if(is_in_hash(pot, hash_table))
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
int try_to_insert_end(stat_link sl)
{
    if(sl == NULL) return 0;
    stat_link nsl = clone_st(sl);
    int h = BKDR_hash(nsl);
    if(h < 0) return 0;
    stat_link u = hash_table_end[h];
    while (u)
    {
        if(memcmp(u->puz[0], nsl->puz[0], sizeof(nsl->puz[0])) == 0 && memcmp(u->puz[1], nsl->puz[1], sizeof(nsl->puz[1])) == 0)
            return 0;
        u = u->next;
    }
    stat_link tmp = hash_table_end[h];
    hash_table_end[h] = nsl;
    hash_table_end[h]->next = tmp;
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
int get_reverse(int d)
{
    switch (d)
    {
        case 1:
            return 3;
        case 2:
            return 4;
        case 3:
            return 1;
        case 4:
            return 2;
    }
    return 1;
}
int print_st(stat_link p1, stat_link p2)
{
    if(p1 == NULL || p2 == NULL) return 0;
    if(p1->ft_len + p2->ft_len == 0)
    {
        printf("PUZZLE ALREADY SOLVED");
    }
    else
    {
        for(int i = 0; i <= p1->ft_len - 1; i++)
            printf("%d", p1->ft[i]);
        for(int i = p2->ft_len - 1; i >=0 ; i--)
            printf("%d", get_reverse(p2->ft[i]));
    }
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
    try_to_insert(elem);//insert into the hash
    push(elem);
    stat_link elem_end = NULL;
    elem_end = new stat();
    memmove(elem_end->puz[0], best_left, sizeof(elem_end->puz[0]));//memcpy and strcpy for memory overlap problem
    memmove(elem_end->puz[1], best_right, sizeof(elem_end->puz[1]));
    try_to_insert_end(elem_end);//insert into the hash
    push_end(elem_end);
    bool is_conn = false;
    stat_link f1 = NULL, f2 = NULL;//start -> f1 -> f2 -> end
    while (!is_empty() && !is_empty_end())
    {
        //start -> end
        stat_link father = pop(), child = NULL;
        if(is_reached(father))
        {
            if((f1 == NULL && f2 == NULL) || ((father->ft_len + find_stat->ft_len) < (f1->ft_len + f2->ft_len)))
            {
                if(f1 != NULL)
                {
                    delete f1;
                    f1 = NULL;
                }
                if(f2 != NULL)
                {
                    delete f2;
                    f2 = NULL;
                }
                f1 = clone_st(father);
                f2 = clone_st(find_stat);
            }
            is_conn = true;
        }
        //one turn complete
        if(is_conn && (is_empty() || front->ft_len != father->ft_len))
        {
            res = f1;
            res_end = f2;
            return 1;
        }
        if(father->ft_len >= 8)
        {
            delete father;
            father = NULL;
            continue;
        }
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
            if(child->ft_len <= 8 && try_to_insert(child))
                push(child);
            else
            if(child != NULL) delete child;
            child = NULL;
        }
        if(father != NULL) delete father;
        father = NULL;
        //end -> start
        stat_link father_end = pop_end(), child_end = NULL;
        if(is_reached_end(father_end))
        {
            if((f1 == NULL && f2 == NULL) || ((father_end->ft_len + find_stat->ft_len) < (f1->ft_len + f2->ft_len)))
            {
                if(f1 != NULL)
                {
                    delete f1;
                    f1 = NULL;
                }
                if(f2 != NULL)
                {
                    delete f2;
                    f2 = NULL;
                }
                f2 = clone_st(father_end);
                f1 = clone_st(find_stat);
            }
            is_conn = true;
        }
        //one turn complete
        if(is_conn && (is_empty_end() || end_front->ft_len != father_end->ft_len))
        {
            res = f1;
            res_end = f2;
            return 1;
        }
        if(father_end->ft_len >= 8)
        {
            delete father_end;
            father_end = NULL;
            continue;
        }
        //generate children from the father
        for(int m = 1; m <= 4 ; m++)//m is mode, 1 ~ 4 indicate that left+clockwise, right+clockwise ......
        {
            child_end = clone_st(father_end);
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
                tmp[next_i] = child_end->puz[whe][i];
            }
            memmove(child_end->puz[whe], tmp, sizeof(child_end->puz[whe]));
            child_end->puz[un_whe][11] = child_end->puz[whe][11];
            child_end->puz[un_whe][10] = child_end->puz[whe][10];
            child_end->puz[un_whe][9] = child_end->puz[whe][9];
            child_end->ft[child_end->ft_len++] = m;
            if(child_end->ft_len <= 16 && try_to_insert_end(child_end))
                push_end(child_end);
            else
            if(child_end != NULL) delete child_end;
            child_end = NULL;
        }
        if(father_end != NULL) delete father_end;
        father_end = NULL;
    }
    return 0;
}
int clear_queue()
{
    stat_link pot = front;
    stat_link tmp = NULL;
    while(!is_empty() && pot)
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
int clear_queue_end()
{
    stat_link pot = end_front;
    stat_link tmp = NULL;
    while(!is_empty_end() && pot)
    {
        tmp = pot;
        pot = pot->next;
        end_front = pot;
        if(tmp != NULL) delete tmp;
        tmp = NULL;
    }
    if(res_end != NULL) delete res_end;
    end_front = end_rear = res_end = NULL;
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
int clear_hash_end()
{
    for(int i = 0; i <= DM - 1; i++)
    {
        stat_link pot = hash_table_end[i];
        while (pot != NULL)
        {
            stat_link tmp = pot;//hash_table must save new struct that is different from queue's struct
            pot = pot->next;//I know why double free, see try_to_insert() carefully, the insert elem is queue elem , it is same struct , so when queue is clear then the hash_table's elem is deleted too
            if(tmp != NULL) delete tmp;//maybe the memory is overlap
            tmp = NULL;
        }
        hash_table_end[i] = NULL;
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
                print_st(res, res_end);
            else
                printf("NO SOLUTION WAS FOUND IN 16 STEPS\n");
            clear_queue();
            clear_queue_end();
            clear_hash();//double free error
            clear_hash_end();
        }
    }
    return 0;
}