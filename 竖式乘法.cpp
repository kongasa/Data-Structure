#include<cstdio>
#include<iostream>
using namespace std;

int a[101];
int b[101];
int pro[101][101];
int len[101];
int ans[201];
int lena;
int lenb;
int lenans;
int cnt;
void print();

void f(int a[], int len) {       //把pro[i]变为正常数
	int tmp = len;
	for (; tmp >= 1; --tmp) {
		if (a[tmp] >= 10) {
			a[tmp - 1] += a[tmp] / 10;
			a[tmp] %= 10;
		}
	}
}

int main() {
	char ch;
	while ((ch = getchar()) == '0') {}
	a[++lena] = ch - '0';
	while ((ch = getchar()) != '\n') {
		a[++lena] = ch - '0';
	}
	while ((ch = getchar()) == '0') {}
	b[++lenb] = ch - '0';
	while ((ch = getchar()) != '\n') {
		b[++lenb] = ch - '0';
	}

	/*for (int i = 1; i <= lena; ++i) {
		printf("%d", a[i]);
	}
	cout << endl;*/

	int i, j;
	for (i = 1; i <= lenb; ++i) {
		if (b[lenb - i + 1] == 0) {
			++cnt;
			len[i] = 0;
			continue;
		}
		for (j = lena; j >= 1; --j) {
			pro[i][j] = b[lenb - i + 1] * a[j];
		}
		f(pro[i], lena);
		if (pro[i][0] == 0) len[i] = lena;
		else len[i] = lena + 1;
		int k;
		for (k = 0, j = lena + lenb - i; j >= lena + lenb - i - len[i] + 1; --j, ++k) {
			ans[j] += pro[i][lena - k];
		}
	}
	f(ans, lena + lenb - 1);
	if (ans[0] == 0) lenans = lena + lenb - 1;
	else lenans = lena + lenb;

	print();
	return 0;
}

void print() {
	int i, j;
	for (i = 1; i <= lenans - lena; ++i) {
		printf("%c", ' ');
	}
	for (i = 1; i <= lena; ++i) {
		printf("%d", a[i]);
	}
	cout << endl;
	for (i = 1; i <= lenans - lenb; ++i) {
		printf("%c", ' ');
	}
	for (i = 1; i <= lenb; ++i) {
		printf("%d", b[i]);
	}
	cout << endl;
	for (i = 1; i <= lenans; ++i) {
		printf("%c", '-');
	}
	cout << endl;
	if (cnt < lenb - 1) {
		for (i = 1; i <= lenb; ++i) {
			if (len[i] == 0) continue;
			for (j = 1; j <= lenans - i + 1 - len[i]; ++j) {
				printf("%c", ' ');
			}
			for (j = lena + 1 - len[i]; j <= lena; ++j) {
				printf("%d", pro[i][j]);
			}
			cout << endl;
		}
		for (i = 1; i <= lenans; ++i) {
			printf("%c", '-');
		}
		cout << endl;
		
	}
	for (i = lena + lenb - lenans; i <= lena + lenb - 1; ++i) {
		printf("%d", ans[i]);
	}
	cout << endl;
}