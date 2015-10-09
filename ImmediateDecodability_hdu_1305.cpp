#include<stdio.h>
#include<string>
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
string in_str;
vector<string> strs;
int strs_len=0;
int cases=0;
bool comp(string s1,string s2) {return(s1.length() < s2.length());}
bool is_prefix(string s1,string s2)
{
    if(s1.length()>s2.length())
    {
        string tmp = s1;
        s2 = s1;
        s1 = tmp;
    }
    if(s1 == s2.substr(0,s1.length())) return(true);
    else return(false);
}
int main()
{
    while(cin>>in_str)
    {
        if(in_str=="9")
        {
            int flag=1;
            cases++;
            sort(strs.begin(),strs.end(),comp);
            for(vector<string>::size_type i= 0;i<=strs.size()-1-1;i++)
            {
                for(vector<string>::size_type j=i+1;j<=strs.size()-1;j++)
                {
                    if(is_prefix(strs[i],strs[j]))
                    {
                        flag=0;
                        break;
                    }
                }
                if(!flag) break;
            }
            if(!flag) printf("Set %d is not immediately decodable\n",cases);
            else    printf("Set %d is immediately decodable\n",cases);
            //clear
            strs.clear();
        }
        else
        {
            strs.push_back(in_str);
        }
    }
    return(0);
}
