#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#include<queue>
#include<algorithm>
using namespace std;
struct State
{
    int step;
    int x,y;
    string vis[6];
};
string Convers(State t)
{
    string tmp;
    for(int i=0; i<5; ++i)
        tmp+=t.vis[i];
    return tmp;
}
map<string,bool> mp;
int M[8][3]= {{1,-2},{-1,-2},{1,2},{-1,2},{2,1},{2,-1},{-2,-1},{-2,1}};
int main()
{
    string dest="111110111100 110000100000";
    int T;
    cin>>T;
    cin.ignore();
    while(T--)
    {
        mp.clear();
        State st;
        for(int i=0; i<5; ++i)
            getline(cin,st.vis[i]);
        string stt=Convers(st);
        if(stt==dest)  printf("Solvable in 0 move(s).\n");
        else
        {
            for(int i=0; i<5; ++i)
            {
                for(int j=0; j<st.vis[i].size(); ++j)
                {
                    if(st.vis[i][j]==' ')
                    {
                        st.x=i;
                        st.y=j;
                        break;
                    }
                }
            }
            st.step=0;
            queue<State> q;
            q.push(st);
            mp[stt]=true;
            int ans=0;
            bool ok=false;
            while(!q.empty()&&!ok)
            {
                State tmp=q.front();
                if(tmp.step==10) break;
                q.pop();
                for(int i=0; i<8&&!ok; ++i)
                {
                    int nx=tmp.x+M[i][0],ny=tmp.y+M[i][1];
                    if(nx<0||ny<0||nx>4||ny>4) continue;
                    State t=tmp;
                    swap(t.vis[nx][ny],t.vis[tmp.x][tmp.y]);
                    t.x=nx;
                    t.y=ny;
                    t.step=tmp.step+1;
                    string tt=Convers(t);
                    if(tt==dest)
                    {
                        ok=true;
                        ans=t.step;
                        break;
                    }
                    if(mp[tt])  continue;
                    else
                    {
                        mp[tt]=true;
                        q.push(t);
                    }
                }
            }
            if(ok)
                printf("Solvable in %d move(s).\n",ans);
            else
                puts("Unsolvable in less than 11 move(s).");
        }
    }
    return 0;
}
