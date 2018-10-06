#include<cstdio>
#include<iostream>
using namespace std;

struct node {
	int w;
	int h;
	node(int ww = 0, int hh = 0) { w = ww; h = hh; }
};

int n;
node a[1001];
node queue[1001];
int length = 0;

void push_back(int w, int h) {
	queue[++length] = node(w, h);
}

node pop() {
	node ans = queue[length--];
	return ans;
}

int main() {
	scanf("%d\n[", &n);
	int count = 0;
	char ch;
	int tmp = 0;
	while ((ch = getchar()) != ']') {
		if ('0' <= ch && ch <= '9') {
			tmp += ch - '0';
			while ((ch = getchar()) >= '0' && ch <= '9') {
				tmp = tmp * 10 + ch - '0';
			}
			a[++count] = node(1, tmp);
			tmp = 0;
			if (ch == ']') { break; }
		}
	}

	int i = 1;
	int ans = 0;
	while (i < n && a[i + 1].h >= a[i].h) ++i;
	push_back(1, a[i].h);
	node tmp1;
	for (++i; i <= n; ++i) {
		if (length == 0) {
			push_back(1, a[i].h);
		}
		else if (queue[1].h <= a[i].h) {
			node tmp2 = queue[1];
			while (length > 0) {
				tmp1 = pop();
 				ans += (tmp2.h - tmp1.h) * tmp1.w;
			}
			push_back(1, a[i].h);
		}
		else {
			int ww = 1;
			while (queue[length].h <= a[i].h) {
				tmp1 = pop();
				ww += tmp1.w;
				ans += (a[i].h - tmp1.h) * tmp1.w;
			}
			push_back(ww, a[i].h);
		}
	}
	printf("%d\n", ans);
	return 0;
}