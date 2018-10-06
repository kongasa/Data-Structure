#include<cstdio>
#include<iostream>
using namespace std;

int parent[250005];
int n, m;
int cnt;

int find(int a) {
	if (parent[a] < 0) return a;
	return parent[a] = find(parent[a]);
}

void u(int a, int b) {
	while (parent[a] > 0) a = parent[a];
	while (parent[b] > 0) b = parent[b];
	if (a == b) return;
	if (parent[a] < parent[b]) {
		parent[a] += parent[b];
		parent[b] = a;
	}
	else {
		parent[b] += parent[a];
		parent[a] = b;
	}
}

void update(int i, int j) {
	int num = (i - 1) * m + j;
	parent[num] = -1;
	if (num - m > 0 && parent[num - m] != 0) {
		u(num - m, num);
		if (j > 1 && parent[num - 1] != 0 && find(num) != find(num - 1)) {
			u(num, num - 1);
			--cnt;
		}
	}
	else if (j > 1 && parent[num - 1] != 0) {
		u(num - 1, num);
	}
	else {
		++cnt;
	}
}

int main() {
	scanf("%d%d", &n, &m);
	int i, j;
	int tmp;
	for (i = 1; i <= n; ++i) {
		for (j = 1; j <= m; ++j) {
			scanf("%d", &tmp);
			if (tmp == 0) {
				update(i, j);
			}
		}
	}
	printf("%d\n", cnt);
	return 0;
}