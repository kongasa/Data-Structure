#include<cstdio>
#include<iostream>
using namespace std;

int f(long long b, long long c) {
	long long tmp = c % b;
	while (tmp) {
		c = b;
		b = tmp;
		tmp = c % b;
	}
	return b;
}

int length(long long x) {
	int ans = 0;
	while (x) {
		++ans;
		x /= 10;
	}
	return ans;
}

void yuefen(long long &a, long long &b) {
	long long tmp = f(a, b);
	a /= tmp;
	b /= tmp;
}

int a[34];
long long int b[34];
long long int c[34];

int main() {
	int n;
	scanf("%d", &n);
	int i;
	a[1] = 1;
	b[1] = 0;
	c[1] = 1;
	/*for (i = 1; i <= n; ++i) {
		c *= i;
	}
	for (i = 1; i <= n; ++i) {
		b += c / i;
	}*/
	for (i = 2; i <= n; ++i) {
		long long tmpb = i;
		long long tmpc = i - 1;
		b[i] = a[i - 1] * c[i - 1] + b[i - 1];
		c[i] = c[i - 1];
		yuefen(b[i], tmpc);
		yuefen(c[i], tmpb);
		b[i] = b[i] * tmpb;
		c[i] = c[i] * tmpc;
		a[i] = b[i] / c[i] + 1;
		b[i] %= c[i];
	}
	if (b[n] == 0) {
		cout << a[n] << endl;
	}
	else {
		int lena = length(a[n]), lenc = length(c[n]);
		for (i = 0; i <= lena; ++i) {
			printf("%c", ' ');
		}
		cout << b[n] << endl << a[n] << ' ';
		for (i = 1; i <= lenc; ++i) {
			printf("%c", '-');
		}
		cout << endl;
		for (i = 0; i <= lena; ++i) {
			printf("%c", ' ');
		}
		cout << c[n] << endl;
	}
	return 0;
}