//取模的性质，对某数取模之后最后一定(?)变成周期数列
#include <iostream>
#include <stdio.h>
using namespace std;
int fi(int n)
{
	int i, x = 1, y = 1, t;
	if (n == 1 || n == 2)
		return 1;
	else
	{
		for (i = 1; i <= n - 2; i++)
		{
			t = y;
			y = (x + y) % 2010;
			x = t;
		}
	return y;
	}
}
int main()
{
	long long x;
	scanf("%lld", &x);
	if (x <= 2040)
		printf("%d", fi(int(x)));
	else
	{
		if (x % 2040 == 0)
		printf("%d",fi(2040));
	else
		printf("%d",fi(int(x % 2040)));

	} return 0;
}