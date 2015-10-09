#include<stdio.h>
#include<string>
#include<iostream>
#include<stack>
#include<ctype.h>
using namespace std;
int N=0;
stack<string> in_stack;//get the input string
stack<string> tmp_stack;//get the in_stack data and parse to the string then save back to the in_stack 
int main()
{
    while(scanf("%d",&N)!=EOF)
    {
        for(int t=1;t<=N;t++)
        {
            //initialize
            while(!in_stack.empty())    in_stack.pop();
            string in_str;
            cin>>in_str;
            for(int i=0;i<=(int)in_str.length()-1;i++)
            {
                if(in_str.substr(i,1) == ")")
                {
                    while(!tmp_stack.empty())   tmp_stack.pop();
                    string ele_str;
                    string sum_str = "";
                    while(in_stack.top() != "(")
                    {
                        ele_str=in_stack.top();
                        in_stack.pop();
                        tmp_stack.push(ele_str);
                    }
                    in_stack.pop();
                    //get the tmp_stack data parse to string
                    int sum_num = 0;
                    while(!tmp_stack.empty())
                    {
                        ele_str=tmp_stack.top();
                        tmp_stack.pop();
                        if(isdigit(ele_str[0]))
                        {
                            //get number integer
                            sum_num= sum_num * 10 + ele_str[0] - '0';
                        }
                        else
                        {
                            //get the number + string to strings of number count
                            if(sum_num>0)   for(int j=1;j<=sum_num;j++) sum_str+=ele_str;
                            else    sum_str+=ele_str;
                            sum_num=0;//such as tmp_stack is 4a2ab3ccc
                        }
                    }
                    //the sum_str save back to the in-stack
                    in_stack.push(sum_str);
                }
                else    in_stack.push(in_str.substr(i,1));
            }
            //all ( , ) is not in the in_stack,parse in_stack to tmp_stack and parse it to string answers
            while(!tmp_stack.empty())   tmp_stack.pop();
            string ele_str;
            string sum_str = "";
            while(!in_stack.empty())
            {
                ele_str=in_stack.top();
                in_stack.pop();
                tmp_stack.push(ele_str);
            }
            //get the tmp_stack data parse to string
            int sum_num = 0;
            while(!tmp_stack.empty())
            {
                ele_str=tmp_stack.top();
                tmp_stack.pop();
                if(isdigit(ele_str[0]))
                {
                    //get number integer
                    sum_num= sum_num * 10 + ele_str[0] - '0';
                }
                else
                {
                    //get the number + string to strings of number count
                    if(sum_num>0)   for(int j=1;j<=sum_num;j++) sum_str+=ele_str;
                    else    sum_str+=ele_str;
                    sum_num=0;//such as tmp_stack is 4a2ab3ccc
                }
            }
            cout<<sum_str<<endl;
        }
    }
    return(0);
}
