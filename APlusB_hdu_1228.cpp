#include<stdio.h>
#include<stack>
#include<string>
#include<iostream>
using namespace std;
stack<string> left_char;
stack<string> right_char;
int results_num[100];
int results_len=0;
int get_num(string str)
{
    int num=0;
    if(str=="one") return(1);
    if(str=="two") return(2);
    if(str=="three") return(3);
    if(str=="four") return(4);
    if(str=="five") return(5);
    if(str=="six") return(6);
    if(str=="seven") return(7);
    if(str=="eight") return(8);
    if(str=="nine") return(9);
    return(num);
}
int add_stack(stack<string> a,stack<string>b)
{
    int bigger_len=a.size()>b.size() ? a.size() : b.size();
    int i=0;
    int bit_num=0;
    int carry=0;
    while(i<=bigger_len-1)
    {
        int a_num=0;
        int b_num=0;
        if(!a.empty())
        {
            a_num=get_num(a.top());
            a.pop();
        }
        if(!b.empty())
        {
            b_num=get_num(b.top());
            b.pop();
        }
        bit_num=a_num+b_num+carry;
        carry=bit_num/10;
        bit_num=bit_num%10;
        results_num[i]=bit_num;
        i++;
    }
    results_num[i]=carry;
    if(!carry) results_len=i;
    else results_len=i+1;
    return(0); 
}
int main()
{
    string in_str;//get the input string of strings
    while(1)//use break to end the loop
    {
        while(!left_char.empty()) left_char.pop();
        while(!right_char.empty()) right_char.pop();
        while(cin>>in_str&&in_str!="+")
        {
            left_char.push(in_str);
        }
        while(cin>>in_str&&in_str!="=")
        {
            right_char.push(in_str);
        }
        if(left_char.size()==1&&right_char.size()==1&&left_char.top()=="zero"&&right_char.top()=="zero")//zero + zero =
        {
            break;
        }
        add_stack(left_char,right_char);
        for(int i=results_len-1;i>=0;i--)
        {
            printf("%d",results_num[i]);
        }
        printf("\n");
    }
    return(0);
}
