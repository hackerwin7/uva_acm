#include<stdio.h>
#include<string.h>
#include<string>
#include<algorithm>
using namespace std;
typedef struct team
{
    char name[20];
    int win_ball;
    int lost_ball;
    int score;
    team()
    {
        memset(name,'\0',sizeof(name));
        win_ball=0;
        lost_ball=0;
        score=0;
    }
}team,*team_link;
team team_list[1000];
int N=0;
int len=0;
int find_team(char str[])
{
    int ind=-1;
    for(int i=0;i<=len-1;i++)
    {
        if(strcmp(team_list[i].name,str)==0)
        {
            ind=i;
            break;
        }
    }
    return(ind);
}
int insert_team(char str[])
{
    strcpy(team_list[len].name,str);
    team_list[len].win_ball=0;
    team_list[len].lost_ball=0;
    team_list[len].score=0;
    len++;
    return(len-1);
}
bool scmp(team a,team b)
{
    if(a.score<b.score)
        return false;
    else if(a.score>b.score)
        return true;
    else
        if((a.win_ball-a.lost_ball)<(b.win_ball-b.lost_ball))
            return(false);
        else if((a.win_ball-a.lost_ball)>(b.win_ball-b.lost_ball))
            return(true);
        else
            if(a.win_ball<b.win_ball)
                return(false);
            else if(a.win_ball>b.win_ball)
                return(true);
            else
                return((string)a.name<(string)b.name);
}
int main()
{
    while(scanf("%d",&N)!=EOF)
    {
        len=0;
        for(int i=1;i<=(N*(N-1));i++)
        {
            char astr[20],bstr[20],vs[3];
            int aball,bball,a_index,b_index;
            scanf("%s %s %s %d:%d",astr,vs,bstr,&aball,&bball);
            a_index=find_team(astr);
            b_index=find_team(bstr);
            if(a_index<0) a_index=insert_team(astr);
            if(b_index<0) b_index=insert_team(bstr);
            team_list[a_index].win_ball+=aball;
            team_list[a_index].lost_ball+=bball;
            team_list[b_index].win_ball+=bball;
            team_list[b_index].lost_ball+=aball;
            if(aball>bball)
            {
                team_list[a_index].score+=3;
            }
            else if(aball<bball)
            {
                team_list[b_index].score+=3;
            }
            else
            {
                team_list[a_index].score+=1;
                team_list[b_index].score+=1;
            }
        }
        sort(team_list,team_list+N,scmp);
        for(int i=0;i<=N-1;i++)
        {
            printf("%s %d\n",team_list[i].name,team_list[i].score);
        }
        printf("\n");
    }
    return(0);
}
