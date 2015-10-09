#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES  1
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
int N = 0;
int scores[1000];
int count = 0;
int main()
{
	while (scanf("%d", &N) != EOF&&N > 0)
	{
		for (int i = 0; i <= N - 1; i++)
		{
			scanf("%d", &scores[i]);
		}
		int target = 0;
		count = 0;
		scanf("%d", &target);
		for (int i = 0; i <= N - 1; i++)
		{
			if (target == scores[i])
			{
				count++;
			}
		}
		printf("%d\n", count);
	}
	return(0);
}