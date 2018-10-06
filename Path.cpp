#include<cstdio>
#include<iostream>
using namespace std;

struct node {
	int idx;
	node *next;
	node (int x = 0, node *n = NULL):idx(x), next(n){}
};

node vers[11];
node edges[101];
int edgenum;
int ans;
bool flag[11];
int n, m, start, M;

void insert(int a, int b) {
	node *tmp = vers[a].next;
	vers[a].next = &edges[edgenum++];
	vers[a].next->idx = b;
	vers[a].next->next = tmp;
}

void dfs(int x, int cnt) {
	if (cnt == M) {
		++ans;
		return;
	}
	node *tmp = vers[x].next;
	flag[x] = 1;
	while (tmp != NULL) {
		if (flag[tmp->idx] == 0) {
			dfs(tmp->idx, cnt + 1);
		}
		tmp = tmp->next;
	}
	flag[x] = 0;
}

int main() {
	scanf("%d%d%d%d", &n, &m, &start, &M);
	int i;
	int a, b;
	for (i = 1; i <= m; ++i) {
		scanf("%d%d", &a, &b);
		insert(a, b);
	}
	dfs(start, 0);
	printf("%d\n", ans);
	return 0;
}