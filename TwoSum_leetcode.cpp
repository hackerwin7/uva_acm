#include<stdio.h>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

typedef struct Node
{
    int num;
    int pos;
}Node,*NodeLink;

bool cp(Node a,Node b)
{
    return(a.num<b.num);//认可这样的排序，所以就是由小到大的 增序速度
}

class Solution {
public:
    vector<int> twoSum(vector<int> &numbers, int target) {
        
        vector<int> result;
        vector<Node> arrays;
        for(int i=0;i<=(int)numbers.size();i++)
        {
            Node elem;
            elem.num=numbers[i];
            elem.pos=i;
            arrays.push_back(elem);
        }
        sort(arrays.begin(),arrays.end(),cp);
        int i=0;
        int j=arrays.size()-1;
        while(i<j)
        {
            int sum=arrays[i].num+arrays[j].num;
            if(sum==target)
            {
                if(arrays[i].pos<arrays[j].pos)
                {
                    result.push_back(arrays[i].pos+1);
                    result.push_back(arrays[j].pos+1);
                }
                else
                {
                    result.push_back(arrays[j].pos+1);
                    result.push_back(arrays[i].pos+1);
                }
                break;
            }
            else if(sum>target)
            {
                j--;
            }
            else
            {
                i++;
            }
        }
        return(result);
    }
};

int main()
{
    Solution sample;
    vector<int> numbers;
    int target=9;
    int cnt=0;
    cout<<"count:";
    cin>>cnt;
    while(cnt--)
    {
        int temp=0;
        cin>>temp;
        numbers.push_back(temp);
    }
    vector<int> rs;
    rs=sample.twoSum(numbers,target);
    cout<<"result:"<<rs[0]<<","<<rs[1]<<endl;
    return(0);
}


