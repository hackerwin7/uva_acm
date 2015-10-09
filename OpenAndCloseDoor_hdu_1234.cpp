#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES  1
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
char iden_num[20];//per person
char begin_time[15], end_time[15];//per person's start time and end time
int startest_number, endest_number;//open door's time and close door's time
char startest_num[20], endest_num[20];//open door's person and close door's person
int N = 0, M = 0;//N is cases number or day's number , M is per day's record of per case
int get_number(char str[])
{
	int num = 0;
	int len = strlen(str);
	for (int i = 0; i <= len - 1; i++)
	{
		if (str[i] != ':')
		{
			num = num * 10 + str[i] - '0';
		}
	}
	return(num);
}
int main()
{
	while (scanf("%d", &N) != EOF)
	{
		while (N--)
		{
			scanf("%d", &M);
			startest_number = 235959;
			endest_number = 000000;
			for (int i = 0; i <= M - 1; i++)
			{
				scanf("%s%s%s", iden_num, begin_time, end_time);
				int begin_number = get_number(begin_time);//get the switch time to number
				int end_number = get_number(end_time);//get the switch time to number
				if (begin_number < startest_number)
				{
					startest_number = begin_number;
					strcpy(startest_num, iden_num);
				}
				if (end_number > endest_number)
				{
					endest_number = end_number;
					strcpy(endest_num, iden_num);
				}
			}
			printf("%s %s\n", startest_num, endest_num);
		}
	}
	return(0);
}