#include <stdio.h>
#include <string.h>
typedef struct dom
{
	int ind;
	int l;
	int r;
	bool is_ro;
}dom,* dom_link;
dom dominos[105];
dom queue_dom[105];
bool visit_dominos[105]={false};
int num_cnt[7];//record the left and right number's count
int M=0;//the length of queue_dom
int N=0;//the length of dominos
//dfs the dominos
int dfs_dom(int cur)
{
	if(cur>N-1)
	{
		return(1);
	}
	for(int i=0;i<=N-1;i++)
	{
		if(!visit_dominos[i])
		{
			if(cur>0)
			{
				if(queue_dom[cur-1].r==dominos[i].l)
				{
					visit_dominos[i]=true;
					queue_dom[cur]=dominos[i];
					int flag=dfs_dom(cur+1);
					if(flag!=0) return(1);
					visit_dominos[i]=false;
				}
				else if(queue_dom[cur-1].r==dominos[i].r)
				{
					visit_dominos[i]=true;
					queue_dom[cur]=dominos[i];
					int tmp=queue_dom[cur].l;
					queue_dom[cur].l=queue_dom[cur].r;
					queue_dom[cur].r=tmp;
					queue_dom[cur].is_ro=true;
					int flag=dfs_dom(cur+1);
					if(flag!=0) return(1);
					visit_dominos[i]=false;
				}
			}
			else
			{
				int left_flag=0;
				int right_flag=0;
				for(int j=0;j<=N-1;j++)
				{
					if(num_cnt[dominos[j].l]%2!=0)
					{
						visit_dominos[j]=true;
						queue_dom[cur]=dominos[j];
						int flag=dfs_dom(cur+1);
						if(flag!=0) return(1);
						visit_dominos[j]=false;
						left_flag=1;
						break;
					}
					if(num_cnt[dominos[j].r]%2!=0)
					{
						visit_dominos[j]=true;
						queue_dom[cur]=dominos[j];
						int tmp=queue_dom[cur].l;
						queue_dom[cur].l=queue_dom[cur].r;
						queue_dom[cur].r=tmp;
						queue_dom[cur].is_ro=true;
						int flag=dfs_dom(cur+1);
						if(flag!=0) return(1);
						visit_dominos[j]=false;
						right_flag=1;
						break;
					}
				}
				if(!left_flag&&!right_flag)
				{
					visit_dominos[i]=true;
					queue_dom[cur]=dominos[i];
					int flag=dfs_dom(cur+1);
					if(flag!=0) return(1);
					else return(0);
					//visit_dominos[i]=false;
				}
				else
				{
					return(0);
				}
			}
		}
	}
	return(0);
}
//pre check the dominos
int pre_check()
{
	int odd_cnt=0;
	for(int i=0;i<=7-1;i++)
	{
		if(num_cnt[i]%2!=0) odd_cnt++;
	}
	if(odd_cnt>2) return(0);
	else return(1);
}
//pre check the dominos
int pre_check1()
{
	for(int i=0;i<=N-1;i++)
	{
		if(num_cnt[dominos[i].l]==1&&num_cnt[dominos[i].r]==1) return(0);
	}
	return(1);
}
//main process
int main()
{
	while(scanf("%d",&N)!=EOF)
	{
		memset(num_cnt,0,sizeof(num_cnt));
		for(int i=0;i<=N-1;i++)
		{
			scanf("%d%d",&dominos[i].l,&dominos[i].r);
			dominos[i].ind=i;
			dominos[i].is_ro=false;
			//record the count
			num_cnt[dominos[i].l]++;
			num_cnt[dominos[i].r]++;
		}
		memset(visit_dominos,false,sizeof(visit_dominos));//init
		if(pre_check()&&pre_check1()&&dfs_dom(0))
		{
			//print queue_dom
			for(int i=0;i<=N-1;i++)
			{
				if(queue_dom[i].is_ro) printf("%d -\n",queue_dom[i].ind + 1);
				else printf("%d +\n", queue_dom[i].ind + 1);
			}
		}
		else
		{
			printf("No solution\n");
		}
	}
	return(0);
}