#include<stdio.h>
#include<iostream>
#include<string>
#include<map>
#include<queue>
using namespace std;
map<string, bool> vis_map;
string ar,br,w,z;
queue<string> queue_str;
int try_to_insert_sub(string elem)
{
    string s = "";
    int len_e = elem.length();
    for(int i = 0; i <= len_e - 1; i++)
    {
        if(elem[i] == 'a') s += ar;
        else s += br;
    }
    int len_s = s.length();
    int len_z = z.length();
    if(len_s <= len_z)
    {
        if(s == z) return 1;
        else
            if(!vis_map[s])
            {
                queue_str.push(s);
                vis_map[s] = true;
            }
    }
    else
    {
        for(int i = 0; i <= len_s - len_z; i++)
        {
            string sub_str = s.substr(i, len_z);
            if(sub_str == z) return 1;
            else
                if(!vis_map[sub_str])
                {
                    queue_str.push(sub_str);
                    vis_map[sub_str] = true;
                }
        }
    }
    return 0;
}
int bfs()
{
    vis_map.clear();
    while(!queue_str.empty()) queue_str.pop();
    queue_str.push(w);
    vis_map[w] = true;
    int flag = 0;
    while(!queue_str.empty())
    {
        string elem = queue_str.front();
        queue_str.pop();
        flag = try_to_insert_sub(elem);
        if(flag) break;
    }
    if(flag) printf("YES\n");
    else printf("NO\n");
    return(0);
}
int main()
{
    while((cin>>ar) != NULL)
    {
        cin>>br;
        cin>>w;
        cin>>z;
        if(w.find(z, 0) != string::npos) printf("YES\n");
        else bfs();
    }
    return(0);
}
