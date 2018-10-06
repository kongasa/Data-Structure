#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;

char a[1000001];
char b[100001];
int len1;
int len2;
int nxt[100001];

void make_next() {
	nxt[0] = 0;
	int p = 1;
	int q = 0;
	for (; p < len2; ++p) {
		while (q > 0 && b[p] != b[q]) {
			q = nxt[q - 1];
		}
		if (b[p] == b[q]) {
			++q;
		}
		nxt[p] = q;
	}
}

int main() {
	char ch;
	cin >> a >> b;
	len1 = strlen(a);
	len2 = strlen(b);
	make_next();

	int i = 0, j = 0;
	for (; i < len1; ++i) {
		while (j > 0 && b[j] != a[i]) {
			j = nxt[j - 1];
		}
		if (b[j] == a[i]) {
			++j;
		}
		if (j == len2) {
			printf("%d\n", i - len2 + 1);
			return 0;
		}
	}
}