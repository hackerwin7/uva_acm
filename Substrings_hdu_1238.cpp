/*
the ans string muse be in the shortest string , so we only enum the shortest string , other string even substring we do not need to enum
*/
#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES  1
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<string>
#include<algorithm>
#include<iostream>
using namespace std;
int t = 0, n = 0;
char strs[100][100];
string strss[100];
int nexts[100];//kmp's next array
int max_len = 0;
int get_next(char pat[])
{
	int i = 0,j = -1,len=strlen(pat);
	nexts[0] = -1;
	while (i < len - 1)
	{
		if (j == -1 || pat[i] == pat[j])
		{
			i++; 
			j++;
			if (pat[i] != pat[j])	nexts[i] = j;
			else	nexts[i] = nexts[j];
		}
		else	j = nexts[j];
	}
	return(0);
}
int kmp(char src[], char pat[])//source string and pattern string
{
	int len1 = strlen(src),len2 = strlen(pat);
	int i = 0, j = 0;
	while (i <= len1 - 1 && j <= len2 - 1)
	{
		if (j == -1 || src[i] == pat[j])
		{
			i++;
			j++;
		}
		else	j = nexts[j];
	}
	if (j > len2 - 1) return(i - len2);
	else	return(-1);
}
bool find_kmp(char src[], char pat[])
{
	get_next(pat);
	if (kmp(src, pat) >= 0)	return(true);
	else	return(false);
}
bool find_BF(char src[], char pat[])
{
	int len1 = strlen(src), len2 = strlen(pat);
	int i = 0, j = 0, i1 = 0;
	for (i = 0; i <= len1 - 1; i++)
	{
		for (j = 0, i1 = i; j <= len2 - 1; j++, i1++)
		{
			if (src[i1] != pat[j])	break;
		}
		if (j > len2 - 1){ return(true); }
	}
	return(false);
}
int inverse(char str[])
{
	int i = 0, j = strlen(str) - 1;
	while (i < j)
	{
		char swaps = str[i];
		str[i] = str[j];
		str[j] = swaps;
		i++; j--;
	}
	return(0);
}
int find_comm(char xstr[],int y,int & max_str)//find the common string
{
	if (strlen(xstr) <= max_str)	return(0);//prune ,  we only get the max length string 
	if (y >= n)//max_str through all strs
	{
		if ((int)strlen(xstr) > max_str)	max_str = strlen(xstr);
		return(0);
	}
	else
	{
		char str1[100],str2[100];
		strcpy(str1, xstr);
		strcpy(str2, strs[y]);
		int len1 = strlen(str1);
		int len2 = strlen(str2);
		for (int lens = len1; lens >= 0; lens--)//prune from long to short string can be useful to other prune //enume the substring according to the lens
		{
			for (int i = 0; i <= len1 && i+lens-1<=len1-1; i ++)//if the substring 's start index and end index out of boundary then get out
			{
				char subs[100] = {'\0'};
				char subs_inver[100] = { '\0' };
				for (int k = 0, ki = i; k <= lens - 1; k++, ki++) subs[k] = str1[ki];//get the substring
				if (find_BF(str2, subs)){ find_comm(subs, y + 1, max_str); }//find_kmp TLE //kmp judge the subs whether is the substring of str2, if it is DFS it
				strcpy(subs_inver, subs);
				inverse(subs_inver);//inverse the substring
				if (find_BF(str2, subs_inver)){ find_comm(subs_inver, y + 1, max_str); }
			}
		}
	}
	return(0);
}
int find_comm_loop()
{
	int len = strlen(strs[0]);
	char str_short[100];
	max_len = 0;
	for (int lens = len; lens >= 0; lens--)
	{
		for (int i = 0; i <= len && i + lens - 1 <= len - 1; i++)
		{
			char subs[100] = { '\0' };
			char subs_inver[100] = { '\0' };
			int j = 0;
			for (int k = 0, ki = i; k <= lens - 1; k++, ki++) subs[k] = strs[0][ki];//get the substring
			for (j = 1; j <= n - 1; j++)
			{
				strcpy(subs_inver, subs);
				inverse(subs_inver);
				if (!find_BF(strs[j], subs)&&!find_BF(strs[j],subs_inver)) break;
			}
			if (j > n - 1){ max_len = lens; }
		}
		if (max_len > 0){ return(max_len); }
	}
	return(max_len);
}
bool comp(string s1, string s2)	{ return(s1.length() < s2.length()); }
int main()
{
	while (scanf("%d", &t) != EOF)
	{
		while (t--)
		{
			scanf("%d", &n);
			for (int i = 0; i <= n - 1; i++)		cin >> strss[i]; //scanf("%s", strss[i].c_str());//it's not useful to sort()
			sort(strss, strss + n, comp);//prune the DFS()
			for (int i = 0; i <= n - 1; i++)		strcpy(strs[i], strss[i].c_str());
			int max_str = 0;
			max_str = find_comm_loop();//find_comm(strs[0], 1, max_str);
			printf("%d\n", max_str);
		}
	}
	return(0);
}