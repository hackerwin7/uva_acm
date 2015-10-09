#include<stdio.h>
#include<string.h>
#define LL 20
#define X 28 //x sum count = 7*4
typedef struct pot
{
    int m;//the number of the 'o'
    int n;//the number of the 'x'
    bool is_various;//if m > 0 and n > 0 then is_various = true
    int x;//the coordinate of x,(0,0) is origin point
    int y;//the coordinate of y,(0,0) is origin point
    pot()
    {
        m=0;
        n=0;
        is_various=false;
        x=0;
        y=0;
    }
}pot,*pot_link;
typedef struct grid
{
    int r;
    int c;
    pot val[LL][LL];
    grid()
    {
        r=0;
        c=0;
    }
}grid,*grid_link;
char grids[500][LL][LL];//save the possible complete grid (no '.' only 'o' or 'x')
int cnt=0;//count of the grids
int used_grids[500]={0};//0 is not visited  x>0 is cur==x  we visited it
char in_grid[LL][LL];//input grid
char place_grid[LL][LL];//after place the 7 boats into in_grid successfully
grid pot_grid;//save the cases of pot in grid
int var_cnt=0;//various pot 's  count
int W=0,H=0;//the input grid 's width and height
int R=0,C=0;//the input of row and col
int cases=0;
int x_cnt=0;//x count of input
int o_cnt=0;//o count of input
int i_cnt=0;//. count of input and x_cnt + o_cnt + i_cnt == W * H
//the 7 kinds of boat all patterns include per kind and rotate 4 times
char patterns[19][10][10]=
{
  {
      "xx",//1 kind -> 1 pattern
      "xx"
  },
  {
      "xx",//1 kind-> 2 patterns
      " xx"
  },
  {
      " x",
      "xx",
      "x"
  },
  {
      " xx",//1 kind -> 2 patterns
      "xx"
  },
  {
      "x ",
      "xx",
      " x"
  },
  {
      "x",//1 kind -> 4 patterns
      "xxx"
  },
  {
      "xx",
      "x",
      "x"
  },
  {
      "xxx",
      "  x"
  },
  {
      " x",
      " x",
      "xx"
  },
  {
      " x ",//1 kind -> 4 patterns
      "xxx"
  },
  {
      "x",
      "xx",
      "x"
  },
  {
      "xxx",
      " x"
  },
  {
      " x",
      "xx",
      " x"
  },
  {
      "  x",//1 kind -> 4 patterns
      "xxx"
  },
  {
      "x",
      "x",
      "xx"
  },
  {
      "xxx",
      "x"
  },
  {
      "xx",
      " x",
      " x"
  },
  {
      "xxxx"//1 kind -> 2 patterns
  },
  {
      "x",
      "x",
      "x",
      "x"
  }
};
int kind_cnt[7]={1,2,2,4,4,4,2};//kind count of the 7 kind of boats, i(begin with 0) kind jth pattern is patterns[kind_cnt[0]+kind_cnt[1]+......+kind_cnt[i-1]+j]
int kind_ind[7]={0,1,3,5,9,13,17};//kind index in the patterns array
//in_grid  deal -> ('z','x'->'x'  'o','.'->'o')
int insert_grid()
{
    //insert the in_grid to grids
    for(int i=0;i<=R-1;i++)
    {
        for(int j=0;j<=C-1;j++)
        {
            if(in_grid[i][j]=='.') {grids[cnt][i][j]='o';}
            else if(in_grid[i][j]>=0&&in_grid[i][j]<=6) {grids[cnt][i][j]='x';}
            else {grids[cnt][i][j]=in_grid[i][j];}
        }
    }
    cnt++;
    if(cnt>=1000) {cnt--;}//exceed the boundary
    return(0);
}
//place next patterns and insert the complete grid into the grids
int DFS_kind(int cur)
{
    if(x_cnt>28) {return(0);}
    if(cnt>R*C) {return(-1);}
    if(cur>=7)
    {
        //debug############################
//        for(int i=0;i<=R-1;i++)
//        {
//            for(int j=0;j<=C-1;j++)
//            {
//                if(in_grid[i][j]>=0&&in_grid[i][j]<=6) {printf("%c",in_grid[i][j]+48);}
//                else printf("%c",in_grid[i][j]);
//            }
//            printf("\n");
//        }
//        printf("\n");
        int x_c=0;
        for(int i=0;i<=R-1;i++)
        {
            for(int j=0;j<=C-1;j++)
            {
                if(in_grid[i][j]=='x'||(in_grid[i][j]>=0&&in_grid[i][j]<=6)) {x_c++;}
            }
        }
        if(x_c==28)//4(point) * 7(boat pattern)
        {
            insert_grid();//in_grid -> place_grid('z','x'->'x'  'o','.'->'o') and not insert the repeat gird
        }
    }
    else
    {
        //scan this kind of all specific patterns
        for(int k=0;k<=kind_cnt[cur]-1;k++)
        {
            int pat_ind=kind_ind[cur]+k;
            //translation the pattern's origin point from (0,0) .... to ... (R-1,C-1)
            for(int nexti=0;nexti<=R-1;nexti++)
            {
                for(int nextj=0;nextj<=C-1;nextj++)
                {
                    //scan the patterns and in_grid by nexti,nextj
                    int i=0,j=0;
                    int match_cnt=0;
                    //record the previous value to reverse
                    int pre_x[5]={0};
                    int pre_y[5]={0};
                    char pre_char[5]={0};
                    while(i<=4-1&&j<=4-1)
                    {
                        char ch=patterns[pat_ind][i][j];
                        if(ch!='\0')
                        {
                            if(ch=='x')
                            {
                                if(nexti+i>R-1||nextj+j>C-1) {break;}//exceed boundary,it must no be matched
                                if(in_grid[nexti+i][nextj+j]=='x'||in_grid[nexti+i][nextj+j]=='.')//matched
                                {
                                    if(in_grid[nexti+i][nextj+j]=='.') {x_cnt++;}
                                    pre_x[match_cnt]=nexti+i;
                                    pre_y[match_cnt]=nextj+j;
                                    pre_char[match_cnt]=in_grid[nexti+i][nextj+j];
                                    match_cnt++;
                                    in_grid[nexti+i][nextj+j]=cur;//the current cur turn we mark it to indicate that this point have been visited at curth turn
                                }
                                else {break;}//the in_grid[nexti+i][nextj+j]=='o' or 'z',not matched
                            }
                        }
                        j++;
                        if(j>4-1)
                        {
                            j=0;
                            i++;
                        }
                    }
                    if(match_cnt==4)//is matched this kind dfs next kind
                    {
                        int flag=DFS_kind(cur+1);
                        if(flag==-1) {return(-1);}
                    }
                    //reverse the z -> x or .
                    for(int ci=0;ci<=match_cnt-1;ci++) {in_grid[pre_x[ci]][pre_y[ci]]=pre_char[ci];if(pre_char[ci]=='.') {x_cnt--;}}
                }
            }
        }
    }
    return(0);
}
//construct the pot_grid
int constr_pot()
{
    //construct the pot_grid
    for(int c=0;c<=cnt-1;c++)
    {
        for(int i=0;i<=R-1;i++)
        {
            for(int j=0;j<=C-1;j++)
            {
                if(grids[c][i][j]=='x') {pot_grid.val[i][j].n++;}
                else {pot_grid.val[i][j].m++;}
            }
        }
    }
    //construct the is_various
    for(int i=0;i<=R-1;i++)
    {
        for(int j=0;j<=C-1;j++)
        {
            if(pot_grid.val[i][j].m>0&&pot_grid.val[i][j].n>0) {pot_grid.val[i][j].is_various=true;var_cnt++;}
        }
    }
    return(0);
}
//sub the char c in the all min_m.x min_m.y in the grids
int sub_grids(pot min_m,char ch,int cur)
{
    for(int c=0;c<=cnt-1;c++)
    {
        if(!used_grids[c]&&grids[c][min_m.x][min_m.y]==ch)
        {
            used_grids[c]=cur;
            for(int i=0;i<=R-1;i++)
            {
                for(int j=0;j<=C-1;j++)
                {
                    if(grids[c][i][j]=='x') {pot_grid.val[i][j].n--;}
                    else {pot_grid.val[i][j].m--;}
                    if(!(pot_grid.val[i][j].m>0&&pot_grid.val[i][j].n>0)) {pot_grid.val[i][j].is_various=false;}
                }
            }
        }
    }
    return(0);
}
//add the char c in the used_grids[x] == cur in the pot_grid,reverse the sub
int add_grids(int cur)
{
    for(int c=0;c<=cnt-1;c++)
    {
        if(used_grids[c]==cur)
        {
            used_grids[c]=0;
            for(int i=0;i<=R-1;i++)
            {
                for(int j=0;j<=C-1;j++)
                {
                    if(grids[c][i][j]=='x') {pot_grid.val[i][j].n++;}
                    else {pot_grid.val[i][j].m++;}
                    if(pot_grid.val[i][j].m>0&&pot_grid.val[i][j].n>0) {pot_grid.val[i][j].is_various=true;}
                }
            }
        }
    }
    return(0);
}
//dfs  the pot_grid and eliminate the various pot,the use_o must <= 1 , cur is the count of turn it must > 0
int DFS_pot(int cur,int use_o)
{
    if(use_o>=2) {return(0);}//have used 'o' twice or more times then it is false
    //find various pot , minimum m
    pot min_m;
    int flag=0;
    int mark=0;
    min_m.m=1000;
    for(int i=0;i<=R-1;i++)
    {
        for(int j=0;j<=C-1;j++)
        {
            if(pot_grid.val[i][j].is_various)
            {
                flag=1;
                if(pot_grid.val[i][j].m<min_m.m)
                {
                    min_m.m=pot_grid.val[i][j].m;
                    min_m.n=pot_grid.val[i][j].n;
                    min_m.x=i;
                    min_m.y=j;
                }
            }
        }
    }
    if(!flag) {return(1);}//no 'o' we direct get yes
    //suppose the min_m pot is 'o' so we eliminate the 'x' of grids
    sub_grids(min_m,'x',cur);
    //dfs
    mark=DFS_pot(cur+1,use_o+1);
    if(!mark) {return(0);}//if false then all false
    //reverse the  suppose of the min_m pot is 'o'
    add_grids(cur);
    //suppose the min_m pot is 'x'
    sub_grids(min_m,'o',cur);
    //dfs
    mark=DFS_pot(cur+1,use_o);
    if(!mark) {return(0);}//if false then all false
    //reverse the  suppose of the min_m pot is 'x'
    add_grids(cur);
    return(1);
}
//test function DFS_place_grid
int test()
{
    while(scanf("%d%d",&W,&H)!=EOF&&(W+H)>0)
    {
        R=H;
        C=W;
        cnt=0;
        x_cnt=o_cnt=i_cnt=0;
        pot_grid.r=R;
        pot_grid.c=C;
        memset(grids,'\0',sizeof(grids));
        for(int i=0;i<=R-1;i++)
        {
            scanf("%s",in_grid[i]);
        }
        DFS_kind(0);//place next patterns and insert the complete grid into the grids
        //debug#############################
        printf("cnt=%d\n",cnt);
        for(int c=0;c<=cnt-1;c++)
        {
            for(int i=0;i<=R-1;i++)
            {
                printf("%s\n",grids[c][i]);
            }
            printf("\n");
        }
    }
    return(0);
}
int main1()
{
    test();
    return(0);
}
int main()
{
    //note!! this problem in uva(322) is input is W H  but in poj(1138) is H W, current version is for uva
    while(scanf("%d%d",&W,&H)!=EOF&&(W+H)>0)
    {
        R=H;
        C=W;
        cnt=0;
        x_cnt=o_cnt=i_cnt=0;
        pot_grid.r=R;
        pot_grid.c=C;
        var_cnt=0;
        memset(grids,'\0',sizeof(grids));
        memset(used_grids,0,sizeof(used_grids));
        for(int i=0;i<=R-1;i++)//initialize the pot_grid
        {
            for(int j=0;j<=C-1;j++)
            {
                pot_grid.val[i][j].is_various=false;
                pot_grid.val[i][j].m=pot_grid.val[i][j].n=pot_grid.val[i][j].x=pot_grid.val[i][j].y=0;
            }
        }
        printf("Game #%d\n",++cases);
        for(int i=0;i<=R-1;i++)
        {
            scanf("%s",in_grid[i]);
            for(int j=0;j<=C-1;j++)
            {
                switch(in_grid[i][j])
                {
                case 'x':
                    x_cnt++;
                    break;
                case 'o':
                    o_cnt++;
                    break;
                case '.':
                    i_cnt++;
                    break;
                }
            }
        }
        //prune
        if(x_cnt>28)
        {
            printf("no.\n\n");
            continue;
        }
        //dfs the input grid
        DFS_kind(0);//place next patterns and insert the complete grid into the grids
        //debug#############################
//        printf("cnt=%d\n",cnt);
//        for(int c=0;c<=cnt-1;c++)
//        {
//            for(int i=0;i<=R-1;i++)
//            {
//                printf("%s\n",grids[c][i]);
//            }
//            printf("\n");
//        }
        //construction pot_grid
        constr_pot();
        //debug################################
//        printf("pot grid:\n");
//        for(int i=0;i<=R-1;i++)
//        {
//            for(int j=0;j<=C-1;j++)
//            {
//                printf("%d %d %d#",pot_grid.val[i][j].m,pot_grid.val[i][j].n,pot_grid.val[i][j].is_various);
//            }
//            printf("\n");
//        }
        //dfs the pot_grid and get the  yes or no
        if(cnt>0&&cnt<=R*C&&DFS_pot(1,0)) printf("yes.\n\n");
        else printf("no.\n\n");
    }
    return(0);
}
