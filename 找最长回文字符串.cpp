//寻找字符串中的最长回文串
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int p[1000];
char str[50];
char newstr[100];
int length;
int ans;

int max(int a, int b) {
	return a > b ? a : b;
}

void solve(int i) {
	int j = 0;
	while (true) {
		if (i + j >= length || i - j < 0) {
			return;
		}
		if (newstr[i + j] == newstr[i - j]) {
			++p[i];
		}
		else return;
		++j;
	}
}

int main() {
	scanf("%s", str);

	int i = 0;
	int j;
	newstr[i++] = '#';
	while (str[i / 2] != '\0') {
		newstr[i] = str[i / 2];
		newstr[++i] = '#';
		++i;
	}
	length = strlen(newstr);
	newstr[i] = str[i / 2];
	newstr[i + 1] = '\0';
	printf("%s\n", newstr);

	int furthest = 0;
	int center = 0;
	int mirror;
	p[0] = 1;
	for (i = 1; newstr[i] != '\0'; ++i) {
		if (i >= furthest) {
			solve(i);
			center = i;
			furthest = i + p[i] - 1;
			ans = max(ans, p[i]);
		}
		else {
			mirror = 2 * center - i;
			if (i + p[mirror] - 1 < furthest) {
				p[i] = p[mirror];
			}
			else {
				p[i] = furthest - i + 1;
				j = furthest - i + 1;;
				while (true) {
					if (i - j < 0 || i + j >= length) {
						break;
					}
					if (newstr[i + j] == newstr[i - j]) {
						++p[i];
					}
					else break;
					++j;
				}
				furthest = i + p[i] - 1;
				center = i;
				ans = max(ans, p[i]);
			}
		}
	}
	printf("%d\n", ans - 1);
	return 0;
}