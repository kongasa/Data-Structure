#include<cstdio>

struct node {
	int data;
	int idx;
	node(int x = 0, int y = 0) {
		data = x;
		idx = y;
	}
};

node cd[2000001];
int idx[2000001];           //记录编号为i的节点的新编号
int ans[2000001];
int cnt;

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	int i;
	int x, y;
	for (i = 1; i <= n; ++i) {
		scanf("%d", &cd[i].data);
		cd[i].idx = i;
		idx[i] = i;
	}

	for (i = 1; i <= m; ++i) {
		scanf("%d%d", &x, &y);
		if (y == 1) {
			++cd[idx[x]].data;
			node tmp = cd[idx[x]];
			int k = idx[x];
			while (k < n && tmp.data > cd[k + 1].data) {
				cd[k] = cd[k + 1];
				idx[cd[k + 1].idx] = k;
				++k;
			}
			cd[k] = tmp;
			idx[tmp.idx] = k;
			ans[++cnt] = cd[1].idx;
		}
		else {
			--cd[idx[x]].data;
			node tmp = cd[idx[x]];
			int k = idx[x];
			while (k > 1 && tmp.data <= cd[k - 1].data) {
				cd[k] = cd[k - 1];
				idx[cd[k - 1].idx] = k;
				--k;
			}
			cd[k] = tmp;
			idx[tmp.idx] = k;
			ans[++cnt] = cd[1].idx;
		}
	}
	for (i = 1; i <= cnt; ++i) {
		printf("%d\n", ans[i]);
	}
	return 0;
}