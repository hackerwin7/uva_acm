#include<stdio.h>
#include<string.h>
#include<stack>
using namespace std;
int prime[30]={2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113};
char str1[1000];
char str2[1000];
stack<int> mars1,mars2;
int result[1000];
int main()
{
    while(scanf("%s%s",str1,str2)!=EOF&&(strcmp(str1,"0")!=0||strcmp(str2,"0")!=0))
    {
        while(!mars1.empty()) mars1.pop(); //initialize
        while(!mars2.empty()) mars2.pop();
        int num=0,len=0;
        for(int i=0;str1[i]!='\0';i++)//scan string to stack1
        {
            if(str1[i]!=',') num=num*10+str1[i]-'0';
            else { mars1.push(num); num=0;}
        }
        mars1.push(num);
        num=0;
        for(int i=0;str2[i]!='\0';i++)//scan string to stack2
        {
            if(str2[i]!=',') num=num*10+str2[i]-'0';
            else { mars2.push(num); num=0;}
        }
        mars2.push(num);
        int carry=0;
        while(!mars1.empty()||!mars2.empty())
        {
            int num1=0,num2=0;
            if(!mars1.empty())
            {
                num1=mars1.top();
                mars1.pop();
            }
            if(!mars2.empty())
            {
                num2=mars2.top();
                mars2.pop();
            }
            num=num1+num2+carry;
            result[len]=num%prime[len];
            carry=num/prime[len];
            len++;
        }
        if(carry>0) result[len++]=carry;
        printf("%d",result[len-1]);
        for(int i=len-2;i>=0;i--) printf(",%d",result[i]);
        printf("\n");
    }
    return(0);
}
