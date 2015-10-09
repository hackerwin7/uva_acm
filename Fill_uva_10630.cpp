#include <stdio.h>
#define MM 99999999
#define DM 1000000
typedef struct node 
{
    int a;
    int b;
    int c;
    int poured;
    struct node * next;
    node()
    {
        a=0;
        b=0;
        c=0;
        poured=0;
        next = NULL;
    }
}node, * node_lnik;
node * head = NULL;
node * rear = NULL;
int a,b,c,d,d1;//d1 <= d
int t;
node * history[DM];//add the all node no repeat node , no same node will add to the queue and stack
int top;
node * reached_node;
void push(node * elem)
{
    if(elem == NULL) return;
    if(head == NULL || rear == NULL)
    {
        head = elem;
        rear = elem;
        elem->next = NULL;
    }
    else
    {
        rear->next = elem;
        elem->next = NULL;
        rear = elem;
    }
}
node * pop()
{
    if(head == NULL || rear == NULL)
    {
        return NULL;
    }
    else
    {
        if(head == rear)//only 1 elem
        {
            node * ret = head;
            head = rear = NULL;
            return ret;
        }
        else
        {
            node * ret = head;
            head = head->next;
            return ret;
        }
    }
}
void nodecpy(node & n1, node & n2)
{
    n1.a = n2.a;
    n1.b = n2.b;
    n1.c = n2.c;
    n1.poured = n2.poured;
    n1.next = n2.next;
}
void push_stack(node elem)
{
    node * new_elem = new node();
    nodecpy(*new_elem, elem);
    history[top++] = new_elem;
}
bool is_equal(node n1, node n2)
{
    if(n1.a == n2.a && n1.b == n2.b && n1.c == n2.c) return true;
    else return false;
}
bool is_exist(node n)
{
    for(int i = 0; i <= top - 1; i++)
    {
        if(is_equal(*history[i], n))
        {
            if(n.poured >= history[i]->poured) return true;
        }
    }
    return false;
}
bool is_reached(node * elem)
{
    if(elem == NULL) return false;
    int dd = 0;//dd is max of { (a,b,c) < d }
    if(elem->a == d || elem->b == d || elem->c == d)
    {
        if(d1 == d)
        {
            if(elem->poured < reached_node->poured) nodecpy(*reached_node, *elem);
        }
        else
        {
            d1 = d;
            nodecpy(*reached_node, *elem);
        }
        return true;
    }
    else
    {
        if(elem->a < d && elem->a >= d1)
        {
            if(elem->a > d1)
            {
                d1 = elem->a;
                nodecpy(*reached_node, *elem);
            }
            else//elem->a == d1
            {
                if(elem->poured < reached_node->poured) nodecpy(*reached_node, *elem);
            }
        }
        if(elem->b < d && elem->b >= d1)
        {
            if(elem->b > d1)
            {
                d1 = elem->b;
                nodecpy(*reached_node, *elem);
            }
            else
            {
                if(elem->poured < reached_node->poured) nodecpy(*reached_node, *elem);
            }
        }
        if(elem->c < d && elem->c >= d1)
        {
            if(elem->c > d1)
            {
                d1 = elem->c;
                nodecpy(*reached_node, *elem);
            }
            else
            {
                if(elem->poured < reached_node->poured) nodecpy(*reached_node, *elem);
            }
        }
        return false;
    }
}
bool is_queue_empty()
{
    if(head == NULL && rear == NULL) return true;
    else return false;
}
void clear_queue()
{
    if(head == NULL && rear == NULL) return;
    else
    {
        node * pot = head;
        while(pot!=NULL)
        {
            node * temp = pot;
            pot = pot->next;
            delete temp;
            temp = NULL;
        }
        head = rear = NULL;
    }
}
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d%d%d", &a, &b, &c, &d);
        //initialize the queue
        top = 0;
        d1 = 0;
        reached_node = new node();
        reached_node->poured = MM;
        node * elem = new node();
        elem->a=0;
        elem->b=0;
        elem->c=c;
        node his;
        nodecpy(his, *elem);
        push(elem);
        push_stack(his);
        if(is_reached(elem))
        {
            printf("%d %d\n",reached_node->poured, d1);
            clear_queue();
            delete reached_node;
            reached_node = NULL;
            continue;
        }
        while(!is_queue_empty())
        {
            int flag=0;
            elem = pop();
            //generate children that is to say brute pour maney ways to generate many children
            //a pour to b or c
            if(elem->a > 0)
            {
                //pour to b
                if(elem->b < b)
                {
                    node * new_elem = new node();
                    new_elem->b = elem->b + elem->a;
                    if(new_elem->b > b)
                    {
                        int p = b - elem->b;
                        new_elem->a = elem->b + elem->a - b;
                        new_elem->b = b;
                        new_elem->c = elem->c;
                        new_elem->poured = elem->poured + p;
                    }
                    else//elem->a is 0
                    {
                        int p = elem->a;
                        new_elem->a = 0;
                        new_elem->c = elem->c;
                        new_elem->poured = elem->poured + p;
                    }
                    if(!is_exist(*new_elem))
                    {
                        if(is_reached(new_elem)) flag=1;
                        push(new_elem);
                        push_stack(*new_elem);
                    }
                    else delete new_elem;
                }
                //pour to c
                if(elem->c < c)
                {
                    node * new_elem = new node();
                    new_elem->c = elem->c + elem->a;
                    if(new_elem->c > c)
                    {
                        int p = c - elem->c;
                        new_elem->a = elem->c + elem->a - c;
                        new_elem->b = elem->b;
                        new_elem->c = c;
                        new_elem->poured = elem->poured + p;
                    }
                    else
                    {
                        int p = elem->a;
                        new_elem->a = 0;
                        new_elem->b = elem->b;
                        new_elem->poured = elem->poured + p;
                    }
                    if(!is_exist(*new_elem))
                    {
                        if(is_reached(new_elem)) flag=1;
                        push(new_elem);
                        push_stack(*new_elem);
                    }
                    else delete new_elem;
                }
            }
            //b pour to a or c
            if(elem->b > 0)
            {
                //pour to a
                if(elem->a < a)
                {
                    node * new_elem = new node();
                    new_elem->a = elem->a + elem->b;
                    if(new_elem->a > a)
                    {
                        int p = a - elem->a;
                        new_elem->a = a;
                        new_elem->b = elem->a + elem->b - a;
                        new_elem->c = elem->c;
                        new_elem->poured = elem->poured + p;
                    }
                    else
                    {
                        int p = elem->b;
                        new_elem->b = 0;
                        new_elem->c = elem->c;
                        new_elem->poured = elem->poured + p;
                    }
                    if(!is_exist(*new_elem))
                    {
                        if(is_reached(new_elem)) flag=1;
                        push(new_elem);
                        push_stack(*new_elem);
                    }
                    else delete new_elem;
                }
                //pour to c
                if(elem->c < c)
                {
                    node * new_elem = new node();
                    new_elem->c = elem->c + elem->b;
                    if(new_elem->c > c)
                    {
                        int p = c - elem->c;
                        new_elem->a = elem->a;
                        new_elem->b = elem->c + elem->b - c;
                        new_elem->c = c;
                        new_elem->poured = elem->poured + p;
                    }
                    else
                    {
                        int p = elem->b;
                        new_elem->a = elem->a;
                        new_elem->b = 0;
                        new_elem->poured = elem->poured + p;
                    }
                    if(!is_exist(*new_elem))
                    {
                        if(is_reached(new_elem)) flag=1;
                        push(new_elem);
                        push_stack(*new_elem);
                    }
                    else delete new_elem;
                }
            }
            //c pour to a or b
            if(elem->c > 0)
            {
                //pour to a
                if(elem->a < a)
                {
                    node * new_elem = new node();
                    new_elem->a = elem->a + elem->c;
                    if(new_elem->a > a)
                    {
                        int p = a - elem->a;
                        new_elem->a = a;
                        new_elem->b = elem->b;
                        new_elem->c = elem->a + elem->c - a;
                        new_elem->poured = elem->poured + p;
                    }
                    else
                    {
                        int p = elem->c;
                        new_elem->b = elem->b;
                        new_elem->c = 0;
                        new_elem->poured = elem->poured + p;
                    }
                    if(!is_exist(*new_elem))
                    {
                        if(is_reached(new_elem)) flag=1;
                        push(new_elem);
                        push_stack(*new_elem);
                    }
                    else delete new_elem;
                }
                //pour to b
                if(elem->b < b)
                {
                    node * new_elem = new node();
                    new_elem->b = elem->b + elem->c;
                    if(new_elem->b > b)
                    {
                        int p = b - elem->b;
                        new_elem->a = elem->a;
                        new_elem->b = b;
                        new_elem->c = elem->b + elem->c - b;
                        new_elem->poured = elem->poured + p;
                    }
                    else
                    {
                        int p = elem->c;
                        new_elem->a = elem->a;
                        new_elem->c = 0;
                        new_elem->poured = elem->poured + p;
                    }
                    if(!is_exist(*new_elem))
                    {
                        if(is_reached(new_elem)) flag=1;
                        push(new_elem);
                        push_stack(*new_elem);
                    }
                    else delete new_elem;
                }
            }
            delete elem;
            elem = NULL;
        }
        printf("%d %d\n",reached_node->poured, d1);// first compare d1  then  compare poured
        clear_queue();
        delete reached_node;
        reached_node = NULL;
    }
    return(0);
}