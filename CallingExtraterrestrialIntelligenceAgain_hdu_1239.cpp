#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES  1
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<math.h>
#define M 100001
bool prime[M];//0 is not prime number,the index is number , value is bool indicate that this number whether is prime number
int m = 0, a = 0, b = 0, p = 0, q = 0;
bool is_valid(int p, int q)
{
	if (prime[q] && p*q <= m && a * q <= b * p && prime[p] && p <= q) return(true);//prune by arrange this condition's order
	else return(false);
}
int main()
{
	//get prime number
	for (int i = 0; i <= M - 1; i++)
	{
		if (i % 2 == 0) prime[i] = false;
		else prime[i] = true;
	}
	prime[2] = true; prime[1] = false;
	int end = sqrt((double)(M-1));
	for (int i = 3; i <= end; i += 2)
	{
		if (prime[i])
			for (int j = i + i; j <= M - 1; j += i){ prime[j] = false; }
	}
	//input start
	while (scanf("%d%d%d", &m, &a, &b) != EOF && (m + a + b) > 0)
	{
		int upper_limit = sqrt((double)m);
		int max_area = 0;
		int imax = 0, jmax = 0;
		for (int i = upper_limit; i >= 2; i--)
		{
			if (max_area == m) break;//prune the loop
			if (prime[i])
			{
				int j = m / i;
				while (!prime[j] || ! is_valid(i,j)) j--;
				if (i*j > max_area)
				{
					max_area = i * j;
					imax = i;
					jmax = j;
				}
			}
		}
		printf("%d %d\n", imax, jmax);
	}
	return(0);
}